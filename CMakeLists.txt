cmake_minimum_required(VERSION 2.8)

option(ENABLE_USB "Enable usb support" ON)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  include("linux.cmake")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  include("win32.cmake")
endif()
