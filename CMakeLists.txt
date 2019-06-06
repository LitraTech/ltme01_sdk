cmake_minimum_required(VERSION 2.8)

option(BUILD_SHARED_LIBS "Build SDK as a shared/dynamic library" OFF)
option(BUILD_EXAMPLES "Build example programs" OFF)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  include("linux.cmake")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  include("win32.cmake")
endif()

if (BUILD_EXAMPLES)
  add_subdirectory("Examples")
endif()
