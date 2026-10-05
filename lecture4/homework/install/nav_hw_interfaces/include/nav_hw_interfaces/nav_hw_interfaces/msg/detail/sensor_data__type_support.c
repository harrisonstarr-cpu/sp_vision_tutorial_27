// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from nav_hw_interfaces:msg/SensorData.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "nav_hw_interfaces/msg/detail/sensor_data__rosidl_typesupport_introspection_c.h"
#include "nav_hw_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "nav_hw_interfaces/msg/detail/sensor_data__functions.h"
#include "nav_hw_interfaces/msg/detail/sensor_data__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `ranges`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void nav_hw_interfaces__msg__SensorData__rosidl_typesupport_introspection_c__SensorData_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  nav_hw_interfaces__msg__SensorData__init(message_memory);
}

void nav_hw_interfaces__msg__SensorData__rosidl_typesupport_introspection_c__SensorData_fini_function(void * message_memory)
{
  nav_hw_interfaces__msg__SensorData__fini(message_memory);
}

size_t nav_hw_interfaces__msg__SensorData__rosidl_typesupport_introspection_c__size_function__SensorData__ranges(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * nav_hw_interfaces__msg__SensorData__rosidl_typesupport_introspection_c__get_const_function__SensorData__ranges(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * nav_hw_interfaces__msg__SensorData__rosidl_typesupport_introspection_c__get_function__SensorData__ranges(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void nav_hw_interfaces__msg__SensorData__rosidl_typesupport_introspection_c__fetch_function__SensorData__ranges(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    nav_hw_interfaces__msg__SensorData__rosidl_typesupport_introspection_c__get_const_function__SensorData__ranges(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void nav_hw_interfaces__msg__SensorData__rosidl_typesupport_introspection_c__assign_function__SensorData__ranges(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    nav_hw_interfaces__msg__SensorData__rosidl_typesupport_introspection_c__get_function__SensorData__ranges(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool nav_hw_interfaces__msg__SensorData__rosidl_typesupport_introspection_c__resize_function__SensorData__ranges(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember nav_hw_interfaces__msg__SensorData__rosidl_typesupport_introspection_c__SensorData_message_member_array[4] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(nav_hw_interfaces__msg__SensorData, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "seq",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(nav_hw_interfaces__msg__SensorData, seq),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "distance",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(nav_hw_interfaces__msg__SensorData, distance),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "ranges",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(nav_hw_interfaces__msg__SensorData, ranges),  // bytes offset in struct
    NULL,  // default value
    nav_hw_interfaces__msg__SensorData__rosidl_typesupport_introspection_c__size_function__SensorData__ranges,  // size() function pointer
    nav_hw_interfaces__msg__SensorData__rosidl_typesupport_introspection_c__get_const_function__SensorData__ranges,  // get_const(index) function pointer
    nav_hw_interfaces__msg__SensorData__rosidl_typesupport_introspection_c__get_function__SensorData__ranges,  // get(index) function pointer
    nav_hw_interfaces__msg__SensorData__rosidl_typesupport_introspection_c__fetch_function__SensorData__ranges,  // fetch(index, &value) function pointer
    nav_hw_interfaces__msg__SensorData__rosidl_typesupport_introspection_c__assign_function__SensorData__ranges,  // assign(index, value) function pointer
    nav_hw_interfaces__msg__SensorData__rosidl_typesupport_introspection_c__resize_function__SensorData__ranges  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers nav_hw_interfaces__msg__SensorData__rosidl_typesupport_introspection_c__SensorData_message_members = {
  "nav_hw_interfaces__msg",  // message namespace
  "SensorData",  // message name
  4,  // number of fields
  sizeof(nav_hw_interfaces__msg__SensorData),
  nav_hw_interfaces__msg__SensorData__rosidl_typesupport_introspection_c__SensorData_message_member_array,  // message members
  nav_hw_interfaces__msg__SensorData__rosidl_typesupport_introspection_c__SensorData_init_function,  // function to initialize message memory (memory has to be allocated)
  nav_hw_interfaces__msg__SensorData__rosidl_typesupport_introspection_c__SensorData_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t nav_hw_interfaces__msg__SensorData__rosidl_typesupport_introspection_c__SensorData_message_type_support_handle = {
  0,
  &nav_hw_interfaces__msg__SensorData__rosidl_typesupport_introspection_c__SensorData_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_nav_hw_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, nav_hw_interfaces, msg, SensorData)() {
  nav_hw_interfaces__msg__SensorData__rosidl_typesupport_introspection_c__SensorData_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  if (!nav_hw_interfaces__msg__SensorData__rosidl_typesupport_introspection_c__SensorData_message_type_support_handle.typesupport_identifier) {
    nav_hw_interfaces__msg__SensorData__rosidl_typesupport_introspection_c__SensorData_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &nav_hw_interfaces__msg__SensorData__rosidl_typesupport_introspection_c__SensorData_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
