cmake_minimum_required(VERSION 3.10)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(FIRE)
include(gtest_build)
include(glfw_build)
find_package(OpenGL REQUIRED)

include(CTest)
enable_testing()

add_subdirectory(FIRE)
add_subdirectory(examples)
