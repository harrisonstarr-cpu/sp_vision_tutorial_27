
#include <chrono>
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "rcl_interfaces/msg/set_parameters_result.hpp"
#include "nav_hw_interfaces/msg/sensor_data.hpp"

class SensorSubscriber : public rclcpp::Node
{
public:
  SensorSubscriber()
      : Node("sensor_subscriber")
  {
    this->declare_parameter("reliability", "reliable");
    this->declare_parameter("depth", 10);

    // 任务二：原值为 30 ms。
    // 发布端为 100 Hz，也就是约每 10 ms 发布一条消息；若订阅回调每次都阻塞 30 ms，
    // 订阅端处理速度会明显跟不上发布速度，队列积压后容易出现序号跳变和丢包。
    // 因此将默认延迟改为 0 ms。
    this->declare_parameter("callback_delay_ms", 0);

    reliability_ = this->get_parameter("reliability").as_string();
    depth_ = this->get_parameter("depth").as_int();
    callback_delay_ms_ = this->get_parameter("callback_delay_ms").as_int();

    setup_subscription();

    report_timer_ = this->create_wall_timer(
        std::chrono::seconds(1), std::bind(&SensorSubscriber::report, this));

    on_set_parameters_callback_handle_ = this->add_on_set_parameters_callback(
        [this](const std::vector<rclcpp::Parameter> &params)
        {
          for (const auto &p : params)
          {
            if (p.get_name() == "callback_delay_ms")
            {
              callback_delay_ms_ = p.as_int();
              RCLCPP_INFO(
                  this->get_logger(), "callback_delay_ms 更新为 %d ms", callback_delay_ms_);
            }
            else if (p.get_name() == "depth")
            {
              depth_ = p.as_int();
              setup_subscription();
            }
            else if (p.get_name() == "reliability")
            {
              reliability_ = p.as_string();
              setup_subscription();
            }
          }
          rcl_interfaces::msg::SetParametersResult result;
          result.successful = true;
          return result;
        });
  }

private:
  void setup_subscription()
  {
    rclcpp::QoS qos{rclcpp::KeepLast(depth_)};
    if (reliability_ == "best_effort")
    {
      qos.reliability(rclcpp::ReliabilityPolicy::BestEffort);
    }
    else
    {
      qos.reliability(rclcpp::ReliabilityPolicy::Reliable);
    }

    subscription_ = this->create_subscription<nav_hw_interfaces::msg::SensorData>(
        "sensor_data", qos,
        std::bind(&SensorSubscriber::topic_callback, this, std::placeholders::_1));

    RCLCPP_INFO(
        this->get_logger(),
        "Subscriber on /sensor_data: reliability=%s, depth=%d",
        reliability_.c_str(), depth_);
  }

  void topic_callback(const nav_hw_interfaces::msg::SensorData::SharedPtr msg)
  {
    if (callback_delay_ms_ > 0)
    {

      std::this_thread::sleep_for(std::chrono::milliseconds(callback_delay_ms_));
    }

    if (!initialized_)
    {
      initialized_ = true;
    }
    else if (msg->seq > expected_seq_)
    {
      const uint32_t lost = msg->seq - expected_seq_;
      RCLCPP_WARN(
          this->get_logger(),
          "检测到丢包: 期望 seq=%u, 实际 seq=%u, 丢失 %u 条",
          expected_seq_, msg->seq, lost);
    }
    else if (msg->seq < expected_seq_)
    {

      RCLCPP_WARN(
          this->get_logger(),
          "seq 回退 (期望 %u, 实际 %u)，重置基准（回绕/多发布者/乱序）",
          expected_seq_, msg->seq);
    }

    expected_seq_ = msg->seq + 1;
    received_count_++;

    RCLCPP_INFO_THROTTLE(
        this->get_logger(), *this->get_clock(), 2000,
        "收到 seq=%u, stamp=%u.%09u, distance=%.3f",
        msg->seq, msg->header.stamp.sec, msg->header.stamp.nanosec, msg->distance);
  }

  void report()
  {
    const uint64_t total = static_cast<uint64_t>(received_count_) + lost_count_;
    const double loss_rate = (total == 0) ? 0.0 : 100.0 * lost_count_ / total;
    RCLCPP_INFO(
        this->get_logger(),
        "累计: 收到 %u 条, 丢失 %u 条, 丢包率 %.2f%%",
        received_count_, lost_count_, loss_rate);
    
          // ---------------- 任务三：计算实际接收帧率 ----------------
      // 记录本次统计时刻。
      const auto now = std::chrono::steady_clock::now();

      // 计算距离上一次统计实际经过了多少秒。
      // 使用真实时间差，而不是简单假设定时器一定严格等于 1.000 s。
      const double elapsed =
        std::chrono::duration<double>(now - last_report_time_).count();

      // received_count_ 是累计值，因此需要减去上一次的累计值，
      // 才能得到这一统计周期中新收到的消息数量。
      const uint32_t received_since_last = received_count_ - last_received_count_;

      // 帧率 = 本统计周期收到的消息数 / 实际经过时间。
      const double fps =
        (elapsed > 0.0) ? static_cast<double>(received_since_last) / elapsed : 0.0;

      RCLCPP_INFO(
        this->get_logger(),
        "接收帧率: %.2f Hz",
        fps);

      // 更新基准，供下一次 report() 使用。
      last_received_count_ = received_count_;
      last_report_time_ = now;


  }

  rclcpp::Subscription<nav_hw_interfaces::msg::SensorData>::SharedPtr subscription_;
  rclcpp::TimerBase::SharedPtr report_timer_;
  rclcpp::node_interfaces::OnSetParametersCallbackHandle::SharedPtr on_set_parameters_callback_handle_;
  std::string reliability_{"reliable"};
  int depth_{10};
  int callback_delay_ms_{0};
  bool initialized_{false};
  uint32_t expected_seq_{0};
  uint32_t received_count_{0};
  uint32_t lost_count_{0};

  // 第三问要用到的两个变量
  uint32_t last_received_count_{0};
  std::chrono::steady_clock::time_point last_report_time_{std::chrono::steady_clock::now()};
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SensorSubscriber>());
  rclcpp::shutdown();
  return 0;
}
