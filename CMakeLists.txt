cmake_minimum_required(VERSION 3.10)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE STRING "" FORCE)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(FIRE)

add_library(CompileOptions INTERFACE)
add_library(FIRE::CompileOptions ALIAS CompileOptions)
if (MSVC)
    target_compile_options(CompileOptions INTERFACE /W4 /WX /EHsc)
else ()
    target_compile_options(CompileOptions INTERFACE -Wall -Wextra -pedantic -Werror)
endif ()
target_compile_features(CompileOptions INTERFACE cxx_std_17)

add_library(MeasureCoverage INTERFACE)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" AND COVERAGE)
    target_compile_options(MeasureCoverage INTERFACE --coverage)
    target_link_libraries(MeasureCoverage INTERFACE --coverage)
endif ()

add_subdirectory(contrib)

find_package(OpenGL REQUIRED)

include(CTest)
enable_testing()

add_subdirectory(FIRE)
add_subdirectory(examples)
