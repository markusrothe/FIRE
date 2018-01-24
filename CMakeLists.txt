cmake_minimum_required(VERSION 3.0)

project(engine)

if (MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_subdirectory(externals/gtest)
add_subdirectory(externals/glfw-3.2.1)
add_subdirectory(externals/glew-2.1.0/build/cmake)
add_subdirectory(externals/glm-0.9.9-a2)

set(header_files
  ./include/assets.h
  ./include/shader.h
  ./include/materialManager.h
  ./include/material.h
  ./include/tokenize.h
  ./include/mesh.h
  ./include/camera.h
  ./include/entity.h
  ./include/materialMap.h
  ./include/materialConfigParser.h
  ./include/compileMaterial.h 
  ./include/renderableManager.h
  ./include/renderable.h
  ./include/sceneComponent.h
  ./include/sceneManager.h 
  ./include/keyhandler.h
  ./include/keyhandlerListener.h
  ./include/window.h
  ./include/texture.h
  ./include/vertexDeclaration.h
  ./include/transform.h
  )

set(src_files
  ./src/shader.cpp
  ./src/materialManager.cpp
  ./src/material.cpp
  ./src/tokenize.cpp
  ./src/mesh.cpp
  ./src/camera.cpp
  ./src/entity.cpp
  ./src/materialMap.cpp
  ./src/materialConfigParser.cpp
  ./src/compileMaterial.cpp
  ./src/renderable.cpp
  ./src/renderableManager.cpp
  ./src/sceneManager.cpp
  ./src/keyhandler.cpp
  ./src/window.cpp
  ./src/texture.cpp
  ./src/vertexDeclaration.cpp
  ./src/transform.cpp
)

include_directories(
  ./include/
)

add_library(engine
  ${src_files} ${header_files}
)

find_package(OpenGL REQUIRED)

target_include_directories (engine PUBLIC
  ${OPENGL_INCLUDE_DIR} 
  externals/glew-2.1.0/include
  externals/stb_image/
)

target_link_libraries(engine glfw ${OPENGL_gl_LIBRARY} glew glm)

target_compile_features(engine PRIVATE cxx_lambda_init_captures)

enable_testing()
add_subdirectory(test)
