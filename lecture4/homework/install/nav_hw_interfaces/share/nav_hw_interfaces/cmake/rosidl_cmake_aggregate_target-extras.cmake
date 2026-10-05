# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target nav_hw_interfaces::nav_hw_interfaces
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${nav_hw_interfaces_TARGETS}.
if(nav_hw_interfaces_TARGETS AND NOT TARGET nav_hw_interfaces::nav_hw_interfaces)
  add_library(nav_hw_interfaces::nav_hw_interfaces INTERFACE IMPORTED)
  set_target_properties(nav_hw_interfaces::nav_hw_interfaces PROPERTIES
    INTERFACE_LINK_LIBRARIES "${nav_hw_interfaces_TARGETS}")
endif()
