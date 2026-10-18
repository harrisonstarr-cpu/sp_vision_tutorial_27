#ifndef PID_CONTROLLER_HPP_
#define PID_CONTROLLER_HPP_

#include <memory>
#include <string>

#include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <geometry_msgs/msg/twist_stamped.hpp>
#include <nav_msgs/msg/path.hpp>
#include <rclcpp/rclcpp.hpp>
#include <tf2_ros/buffer.h>

#include "sp_controller_server/controller_plugin.hpp"

namespace pid_controller {

class PidController : public sp_controller_server::ControllerPlugin {
public:
  PidController() = default;
  ~PidController() override = default;

  void configure(
    const rclcpp::Node::SharedPtr & node, const std::string & plugin_name,
    const std::shared_ptr<tf2_ros::Buffer> & tf_buffer) override;

  void setPlan(const nav_msgs::msg::Path & path) override;

  geometry_msgs::msg::TwistStamped computeVelocityCommands(
    const geometry_msgs::msg::PoseStamped & pose,
    const geometry_msgs::msg::Twist & velocity) override;

private:

  std::string plugin_name_;

  std::shared_ptr<tf2_ros::Buffer> tf_buffer_;

  rclcpp::Node::SharedPtr node_;

  nav_msgs::msg::Path global_plan_;

  std::string base_frame_id_;


  // Pure Pursuit
  double lookahead_distance_;


  // PID
  double kp_;
  double ki_;
  double kd_;

  double integral_x_;
  double integral_y_;

  double last_error_x_;
  double last_error_y_;


  // limit
  double max_speed_;

  rclcpp::Time last_time_;
  

};

}

#endif
