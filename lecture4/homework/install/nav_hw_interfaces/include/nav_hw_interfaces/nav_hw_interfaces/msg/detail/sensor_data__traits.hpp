// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from nav_hw_interfaces:msg/SensorData.idl
// generated code does not contain a copyright notice

#ifndef NAV_HW_INTERFACES__MSG__DETAIL__SENSOR_DATA__TRAITS_HPP_
#define NAV_HW_INTERFACES__MSG__DETAIL__SENSOR_DATA__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "nav_hw_interfaces/msg/detail/sensor_data__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace nav_hw_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const SensorData & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: seq
  {
    out << "seq: ";
    rosidl_generator_traits::value_to_yaml(msg.seq, out);
    out << ", ";
  }

  // member: distance
  {
    out << "distance: ";
    rosidl_generator_traits::value_to_yaml(msg.distance, out);
    out << ", ";
  }

  // member: ranges
  {
    if (msg.ranges.size() == 0) {
      out << "ranges: []";
    } else {
      out << "ranges: [";
      size_t pending_items = msg.ranges.size();
      for (auto item : msg.ranges) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SensorData & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: seq
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "seq: ";
    rosidl_generator_traits::value_to_yaml(msg.seq, out);
    out << "\n";
  }

  // member: distance
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "distance: ";
    rosidl_generator_traits::value_to_yaml(msg.distance, out);
    out << "\n";
  }

  // member: ranges
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.ranges.size() == 0) {
      out << "ranges: []\n";
    } else {
      out << "ranges:\n";
      for (auto item : msg.ranges) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SensorData & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace nav_hw_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use nav_hw_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const nav_hw_interfaces::msg::SensorData & msg,
  std::ostream & out, size_t indentation = 0)
{
  nav_hw_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use nav_hw_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const nav_hw_interfaces::msg::SensorData & msg)
{
  return nav_hw_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<nav_hw_interfaces::msg::SensorData>()
{
  return "nav_hw_interfaces::msg::SensorData";
}

template<>
inline const char * name<nav_hw_interfaces::msg::SensorData>()
{
  return "nav_hw_interfaces/msg/SensorData";
}

template<>
struct has_fixed_size<nav_hw_interfaces::msg::SensorData>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<nav_hw_interfaces::msg::SensorData>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<nav_hw_interfaces::msg::SensorData>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // NAV_HW_INTERFACES__MSG__DETAIL__SENSOR_DATA__TRAITS_HPP_
