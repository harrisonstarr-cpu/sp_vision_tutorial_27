#include "pid_controller.hpp"

#include <pluginlib/class_list_macros.hpp>

#include <rclcpp/exceptions.hpp>

#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>

#include <sstream>
#include <stdexcept>
#include <cmath>
#include <limits>


namespace {

[[noreturn]] void sp_nav_param_error(
    const rclcpp::Node & node,
    const std::string & name)
{
  std::ostringstream oss;
  oss << "[参数缺失] 节点 '" << node.get_name()
      << "' 缺少参数 '" << name
      << "'，请在对应 yaml 的 ros__parameters 中填写。";

  throw std::runtime_error(oss.str());
}


template<typename T>
T require_param(
    const rclcpp::Node::SharedPtr & node,
    const std::string & name)
{
  try {

    if (node->has_parameter(name)) {
      return node->get_parameter(name).get_value<T>();
    }

    return node->declare_parameter<T>(name);

  }
  catch (
    const rclcpp::exceptions::UninitializedStaticallyTypedParameterException &)
  {
    sp_nav_param_error(*node, name);
  }
}

}


namespace pid_controller {


void PidController::configure(
  const rclcpp::Node::SharedPtr & node,
  const std::string & name,
  const std::shared_ptr<tf2_ros::Buffer> & tf_buffer)
{
  node_ = node;
  plugin_name_ = name;
  tf_buffer_ = tf_buffer;


  if (!node_) {
    throw std::runtime_error(
      "PidController received null node");
  }


  base_frame_id_ =
      require_param<std::string>(
          node_,
          plugin_name_ + ".base_frame_id");


  lookahead_distance_ =
      require_param<double>(
          node_,
          plugin_name_ + ".lookahead_distance");


  kp_ =
      require_param<double>(
          node_,
          plugin_name_ + ".kp");


  ki_ =
      require_param<double>(
          node_,
          plugin_name_ + ".ki");


  kd_ =
      require_param<double>(
          node_,
          plugin_name_ + ".kd");


  max_speed_ =
      require_param<double>(
          node_,
          plugin_name_ + ".max_speed");


  integral_x_ = 0.0;
  integral_y_ = 0.0;

  last_error_x_ = 0.0;
  last_error_y_ = 0.0;

  last_time_ = node_->now();


  RCLCPP_INFO(
      node_->get_logger(),
      "[%s] configured: lookahead=%.2f kp=%.2f ki=%.2f kd=%.2f max_speed=%.2f",
      plugin_name_.c_str(),
      lookahead_distance_,
      kp_,
      ki_,
      kd_,
      max_speed_);
}



void PidController::setPlan(
    const nav_msgs::msg::Path & path)
{
  global_plan_ = path;
}



geometry_msgs::msg::TwistStamped
PidController::computeVelocityCommands(
  const geometry_msgs::msg::PoseStamped &,
  const geometry_msgs::msg::Twist &)
{

  geometry_msgs::msg::TwistStamped cmd_vel;

  cmd_vel.header.stamp = node_->now();
  cmd_vel.header.frame_id = base_frame_id_;



  // -----------------------------
  // 1. 检查路径
  // -----------------------------

  if(global_plan_.poses.empty())
  {
    RCLCPP_WARN_THROTTLE(
      node_->get_logger(),
      *node_->get_clock(),
      5000,
      "[%s] global path empty",
      plugin_name_.c_str());

    return cmd_vel;
  }



  // -----------------------------
  // 2. 获取机器人在map中的位置
  // -----------------------------

  double robot_x = 0.0;
  double robot_y = 0.0;
  double yaw = 0.0;


  try
  {

    auto tf =
      tf_buffer_->lookupTransform(
        "map",
        base_frame_id_,
        tf2::TimePointZero);



    robot_x =
      tf.transform.translation.x;

    robot_y =
      tf.transform.translation.y;


    tf2::Quaternion q(
      tf.transform.rotation.x,
      tf.transform.rotation.y,
      tf.transform.rotation.z,
      tf.transform.rotation.w);



    double roll = 0.0;
    double pitch = 0.0;
    tf2::Matrix3x3(q)
	  .getRPY(
	    roll,
	    pitch,
	    yaw);
    
  }
  catch(
    const tf2::TransformException & ex)
  {

    RCLCPP_WARN_THROTTLE(
      node_->get_logger(),
      *node_->get_clock(),
      5000,
      "TF error: %s",
      ex.what());

    return cmd_vel;
  }




  // -----------------------------
  // 3. 找最近路径点
  // -----------------------------

  int nearest_index = 0;

  double min_dist =
      std::numeric_limits<double>::max();



  for(size_t i=0;
      i<global_plan_.poses.size();
      i++)
  {

    double dx =
      global_plan_.poses[i]
      .pose.position.x - robot_x;


    double dy =
      global_plan_.poses[i]
      .pose.position.y - robot_y;


    double dist =
      std::hypot(dx,dy);


    if(dist < min_dist)
    {
      min_dist = dist;
      nearest_index = i;
    }
  }




  // -----------------------------
  // 4. Pure Pursuit寻找前视点
  // -----------------------------

  int target_index =
      nearest_index;



  for(size_t i=nearest_index;
      i<global_plan_.poses.size();
      i++)
  {

    double dx =
      global_plan_.poses[i]
      .pose.position.x - robot_x;


    double dy =
      global_plan_.poses[i]
      .pose.position.y - robot_y;



    if(std::hypot(dx,dy)
       >= lookahead_distance_)
    {
      target_index = i;
      break;
    }
  }




  double target_x =
    global_plan_.poses[target_index]
    .pose.position.x;


  double target_y =
    global_plan_.poses[target_index]
    .pose.position.y;




  // -----------------------------
  // 5. 计算误差(map坐标)
  // -----------------------------

  double error_x =
      target_x - robot_x;


  double error_y =
      target_y - robot_y;




  // -----------------------------
  // 6. P控制
  // -----------------------------

  double vx_map =
      kp_ * error_x;


  double vy_map =
      kp_ * error_y;




  // -----------------------------
  // 7. 限制速度
  // -----------------------------

  double speed =
      std::hypot(vx_map, vy_map);


  if(speed > max_speed_)
  {

    vx_map =
      vx_map / speed * max_speed_;


    vy_map =
      vy_map / speed * max_speed_;

  }




  // -----------------------------
  // 8. map速度转换base_link
  // -----------------------------

  double vx =
      std::cos(yaw) * vx_map
      +
      std::sin(yaw) * vy_map;



  double vy =
      -std::sin(yaw) * vx_map
      +
      std::cos(yaw) * vy_map;




  // -----------------------------
  // 9. 输出cmd_vel
  // -----------------------------

  cmd_vel.twist.linear.x =
      vx;


  cmd_vel.twist.linear.y =
      vy;


  cmd_vel.twist.linear.z =
      0.0;


  cmd_vel.twist.angular.z =
      0.0;



  return cmd_vel;
}



}


PLUGINLIB_EXPORT_CLASS(
  pid_controller::PidController,
  sp_controller_server::ControllerPlugin)
