// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from nav_hw_interfaces:msg/SensorData.idl
// generated code does not contain a copyright notice
#include "nav_hw_interfaces/msg/detail/sensor_data__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `ranges`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
nav_hw_interfaces__msg__SensorData__init(nav_hw_interfaces__msg__SensorData * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    nav_hw_interfaces__msg__SensorData__fini(msg);
    return false;
  }
  // seq
  // distance
  // ranges
  if (!rosidl_runtime_c__float__Sequence__init(&msg->ranges, 0)) {
    nav_hw_interfaces__msg__SensorData__fini(msg);
    return false;
  }
  return true;
}

void
nav_hw_interfaces__msg__SensorData__fini(nav_hw_interfaces__msg__SensorData * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // seq
  // distance
  // ranges
  rosidl_runtime_c__float__Sequence__fini(&msg->ranges);
}

bool
nav_hw_interfaces__msg__SensorData__are_equal(const nav_hw_interfaces__msg__SensorData * lhs, const nav_hw_interfaces__msg__SensorData * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // seq
  if (lhs->seq != rhs->seq) {
    return false;
  }
  // distance
  if (lhs->distance != rhs->distance) {
    return false;
  }
  // ranges
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->ranges), &(rhs->ranges)))
  {
    return false;
  }
  return true;
}

bool
nav_hw_interfaces__msg__SensorData__copy(
  const nav_hw_interfaces__msg__SensorData * input,
  nav_hw_interfaces__msg__SensorData * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // seq
  output->seq = input->seq;
  // distance
  output->distance = input->distance;
  // ranges
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->ranges), &(output->ranges)))
  {
    return false;
  }
  return true;
}

nav_hw_interfaces__msg__SensorData *
nav_hw_interfaces__msg__SensorData__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  nav_hw_interfaces__msg__SensorData * msg = (nav_hw_interfaces__msg__SensorData *)allocator.allocate(sizeof(nav_hw_interfaces__msg__SensorData), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(nav_hw_interfaces__msg__SensorData));
  bool success = nav_hw_interfaces__msg__SensorData__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
nav_hw_interfaces__msg__SensorData__destroy(nav_hw_interfaces__msg__SensorData * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    nav_hw_interfaces__msg__SensorData__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
nav_hw_interfaces__msg__SensorData__Sequence__init(nav_hw_interfaces__msg__SensorData__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  nav_hw_interfaces__msg__SensorData * data = NULL;

  if (size) {
    data = (nav_hw_interfaces__msg__SensorData *)allocator.zero_allocate(size, sizeof(nav_hw_interfaces__msg__SensorData), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = nav_hw_interfaces__msg__SensorData__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        nav_hw_interfaces__msg__SensorData__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
nav_hw_interfaces__msg__SensorData__Sequence__fini(nav_hw_interfaces__msg__SensorData__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      nav_hw_interfaces__msg__SensorData__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

nav_hw_interfaces__msg__SensorData__Sequence *
nav_hw_interfaces__msg__SensorData__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  nav_hw_interfaces__msg__SensorData__Sequence * array = (nav_hw_interfaces__msg__SensorData__Sequence *)allocator.allocate(sizeof(nav_hw_interfaces__msg__SensorData__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = nav_hw_interfaces__msg__SensorData__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
nav_hw_interfaces__msg__SensorData__Sequence__destroy(nav_hw_interfaces__msg__SensorData__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    nav_hw_interfaces__msg__SensorData__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
nav_hw_interfaces__msg__SensorData__Sequence__are_equal(const nav_hw_interfaces__msg__SensorData__Sequence * lhs, const nav_hw_interfaces__msg__SensorData__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!nav_hw_interfaces__msg__SensorData__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
nav_hw_interfaces__msg__SensorData__Sequence__copy(
  const nav_hw_interfaces__msg__SensorData__Sequence * input,
  nav_hw_interfaces__msg__SensorData__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(nav_hw_interfaces__msg__SensorData);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    nav_hw_interfaces__msg__SensorData * data =
      (nav_hw_interfaces__msg__SensorData *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!nav_hw_interfaces__msg__SensorData__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          nav_hw_interfaces__msg__SensorData__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!nav_hw_interfaces__msg__SensorData__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
