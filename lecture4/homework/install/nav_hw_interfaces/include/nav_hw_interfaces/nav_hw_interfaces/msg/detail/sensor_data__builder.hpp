// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from nav_hw_interfaces:msg/SensorData.idl
// generated code does not contain a copyright notice

#ifndef NAV_HW_INTERFACES__MSG__DETAIL__SENSOR_DATA__BUILDER_HPP_
#define NAV_HW_INTERFACES__MSG__DETAIL__SENSOR_DATA__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "nav_hw_interfaces/msg/detail/sensor_data__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace nav_hw_interfaces
{

namespace msg
{

namespace builder
{

class Init_SensorData_ranges
{
public:
  explicit Init_SensorData_ranges(::nav_hw_interfaces::msg::SensorData & msg)
  : msg_(msg)
  {}
  ::nav_hw_interfaces::msg::SensorData ranges(::nav_hw_interfaces::msg::SensorData::_ranges_type arg)
  {
    msg_.ranges = std::move(arg);
    return std::move(msg_);
  }

private:
  ::nav_hw_interfaces::msg::SensorData msg_;
};

class Init_SensorData_distance
{
public:
  explicit Init_SensorData_distance(::nav_hw_interfaces::msg::SensorData & msg)
  : msg_(msg)
  {}
  Init_SensorData_ranges distance(::nav_hw_interfaces::msg::SensorData::_distance_type arg)
  {
    msg_.distance = std::move(arg);
    return Init_SensorData_ranges(msg_);
  }

private:
  ::nav_hw_interfaces::msg::SensorData msg_;
};

class Init_SensorData_seq
{
public:
  explicit Init_SensorData_seq(::nav_hw_interfaces::msg::SensorData & msg)
  : msg_(msg)
  {}
  Init_SensorData_distance seq(::nav_hw_interfaces::msg::SensorData::_seq_type arg)
  {
    msg_.seq = std::move(arg);
    return Init_SensorData_distance(msg_);
  }

private:
  ::nav_hw_interfaces::msg::SensorData msg_;
};

class Init_SensorData_header
{
public:
  Init_SensorData_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SensorData_seq header(::nav_hw_interfaces::msg::SensorData::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_SensorData_seq(msg_);
  }

private:
  ::nav_hw_interfaces::msg::SensorData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::nav_hw_interfaces::msg::SensorData>()
{
  return nav_hw_interfaces::msg::builder::Init_SensorData_header();
}

}  // namespace nav_hw_interfaces

#endif  // NAV_HW_INTERFACES__MSG__DETAIL__SENSOR_DATA__BUILDER_HPP_
