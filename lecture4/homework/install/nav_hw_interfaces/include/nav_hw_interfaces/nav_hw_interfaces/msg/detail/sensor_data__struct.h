// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from nav_hw_interfaces:msg/SensorData.idl
// generated code does not contain a copyright notice

#ifndef NAV_HW_INTERFACES__MSG__DETAIL__SENSOR_DATA__STRUCT_H_
#define NAV_HW_INTERFACES__MSG__DETAIL__SENSOR_DATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'ranges'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/SensorData in the package nav_hw_interfaces.
typedef struct nav_hw_interfaces__msg__SensorData
{
  std_msgs__msg__Header header;
  uint32_t seq;
  float distance;
  rosidl_runtime_c__float__Sequence ranges;
} nav_hw_interfaces__msg__SensorData;

// Struct for a sequence of nav_hw_interfaces__msg__SensorData.
typedef struct nav_hw_interfaces__msg__SensorData__Sequence
{
  nav_hw_interfaces__msg__SensorData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} nav_hw_interfaces__msg__SensorData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // NAV_HW_INTERFACES__MSG__DETAIL__SENSOR_DATA__STRUCT_H_
