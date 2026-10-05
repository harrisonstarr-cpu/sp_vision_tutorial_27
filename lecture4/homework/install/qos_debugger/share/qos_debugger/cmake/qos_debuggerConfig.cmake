# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_qos_debugger_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED qos_debugger_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(qos_debugger_FOUND FALSE)
  elseif(NOT qos_debugger_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(qos_debugger_FOUND FALSE)
  endif()
  return()
endif()
set(_qos_debugger_CONFIG_INCLUDED TRUE)

# output package information
if(NOT qos_debugger_FIND_QUIETLY)
  message(STATUS "Found qos_debugger: 0.0.0 (${qos_debugger_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'qos_debugger' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${qos_debugger_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(qos_debugger_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${qos_debugger_DIR}/${_extra}")
endforeach()
