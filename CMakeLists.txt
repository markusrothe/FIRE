cmake_minimum_required(VERSION 3.0)

project(engine)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (MSVC AND (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 19.11))
  # VS 2017 : Disable warnings from from gtest code, using deprecated code related to TR1 
  add_definitions(-D_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING)
  message("Add flag to disable warnings from gtest -  _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING")
endif()


option(gtest_force_shared_crt "" ON)
option(BUILD_GTEST "" ON)

add_subdirectory(externals/googletest)
add_subdirectory(externals/glfw-3.2.1)
add_subdirectory(externals/glew-2.1.0/build/cmake)
add_subdirectory(externals/glm-0.9.9-a2)
add_subdirectory(externals/freetype-2.9)

set(header_files
  ./include/fire/renderer.h
  ./include/fire/window.h
  ./include/fire/windowFactory.h
  ./include/fire/scene.h
  ./include/fire/sceneManager.h
  ./include/fire/sceneComponent.h
  ./include/fire/renderContext.h
  ./include/fire/renderable.h
  ./include/fire/renderingDelegate.h
  ./include/fire/glRenderContext.h
  ./include/fire/vertexData.h
  ./include/fire/vertexDeclaration.h
  ./include/fire/findByName.h
  ./include/fire/binder.h
  ./include/fire/material.h
  ./include/fire/uniformFunction.h
  ./include/fire/textureBinder.h
  ./include/fire/texture.h
  )

set(src_files
  ./src/fire/renderer.cpp
  ./src/fire/window.cpp
  ./src/fire/windowFactory.cpp
  ./src/fire/scene.cpp
  ./src/fire/sceneManager.cpp
  ./src/fire/sceneComponent.cpp
  ./src/fire/glRenderContext.cpp
  ./src/fire/renderable.cpp
  ./src/fire/vertexData.cpp
  ./src/fire/vertexDeclaration.cpp
  ./src/fire/material.cpp
  ./src/fire/textureBinder.cpp
  )

include_directories(
  ./include/fire/
)

add_library(engine
  ${src_files} ${header_files}
)

if (MSVC)
  target_compile_options(engine PUBLIC /W4)
else()
  target_compile_options(engine PUBLIC -Wall -Wextra -Wpedantic -std=c++17)
endif()

find_package(OpenGL REQUIRED)

target_include_directories (engine SYSTEM PUBLIC
  ${OPENGL_INCLUDE_DIR} 
  externals/glew-2.1.0/include
  externals/stb_image/
  externals/freetype-2.9/include
)

target_link_libraries(engine glfw ${OPENGL_gl_LIBRARY} glew glm freetype)

target_compile_features(engine PRIVATE cxx_lambda_init_captures)

enable_testing()
add_subdirectory(test)

add_subdirectory(examples)
