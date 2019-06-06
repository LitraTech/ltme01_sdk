cmake_minimum_required(VERSION 2.8)

project(ltme01_sdk-examples)

if(NOT BUILD_SHARED_LIBS)
  add_definitions(-DLTME01_SDK_STATIC)
endif()
add_executable(LidarControlller "lidar_controller.cpp")
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  target_link_libraries(LidarControlller ltme01_sdk "WS2_32.Lib")
else()
  target_link_libraries(LidarControlller ltme01_sdk)
endif()
