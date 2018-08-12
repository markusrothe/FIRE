cmake_minimum_required(VERSION 3.0)

project(engine)

find_package(OpenGL REQUIRED)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



if (MSVC AND (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 19.11))	
  # VS 2017 : Disable warnings from from gtest code, using deprecated code related to TR1 	
  add_definitions(-D_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING)	
  message("Add flag to disable warnings from gtest -  _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING")	
endif()

option(gtest_force_shared_crt "" ON)	
option(BUILD_GTEST "" ON)
add_subdirectory(externals/googletest)	

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(externals/glfw-3.2.1)
	
add_subdirectory(externals/glm-0.9.9-a2)

add_definitions(-DGLEW_STATIC=1)
set(glew_header
   ${PROJECT_SOURCE_DIR}/externals/glew-2.1.0/include/GL/glew.h)
   
set(glew_source
    ${PROJECT_SOURCE_DIR}/externals/glew-2.1.0/src/glew.c)

set(header_files
  ./include/fire/renderer.h
  ./include/fire/rendererFactory.h
  ./include/fire/window.h
  ./include/fire/windowFactory.h
  ./include/fire/scene.h
  ./include/fire/sceneManager.h
  ./include/fire/sceneComponent.h
  ./include/fire/renderContext.h
  ./include/fire/renderable.h
  ./include/fire/renderingDelegate.h
  ./include/fire/glRenderContext.h
  ./include/fire/glRenderingDelegate.h
  ./include/fire/vertexData.h
  ./include/fire/vertexDeclaration.h
  ./include/fire/indexData.h
  ./include/fire/findByName.h
  ./include/fire/binder.h
  ./include/fire/material.h
  ./include/fire/materialFactory.h
  ./include/fire/uniformFunction.h
  ./include/fire/shaderParser.h
  )

set(src_files
  ./src/fire/renderer.cpp
  ./src/fire/rendererFactory.cpp
  ./src/fire/window.cpp
  ./src/fire/windowFactory.cpp
  ./src/fire/scene.cpp
  ./src/fire/sceneManager.cpp
  ./src/fire/sceneComponent.cpp
  ./src/fire/shaderParser.cpp
  ./src/fire/glRenderContext.cpp
  ./src/fire/glRenderingDelegate.cpp
  ./src/fire/renderable.cpp
  ./src/fire/vertexData.cpp
  ./src/fire/vertexDeclaration.cpp
  ./src/fire/indexData.cpp
  ./src/fire/material.cpp
  ./src/fire/materialFactory.cpp
  )

include_directories(
  ${PROJECT_SOURCE_DIR}/include/fire/
)

add_library(engine
  ${src_files} ${header_files} ${glew_header} ${glew_source}
)

if (MSVC)
  target_compile_options(engine PUBLIC /W4)
else()
  target_compile_options(engine PUBLIC -Wall -Wextra -Wpedantic -std=c++17 -g -O0)
  
  if (COVERAGE)
    target_compile_options(engine PUBLIC --coverage)
    target_link_libraries(engine --coverage)
  endif()
endif()

target_include_directories (engine SYSTEM PUBLIC
  ${OPENGL_INCLUDE_DIR} 
  ${PROJECT_SOURCE_DIR}/externals/stb_image
  ${PROJECT_SOURCE_DIR}/externals/glm-0.9.9-a2
  ${PROJECT_SOURCE_DIR}/externals/glfw-3.2.1/include
  ${PROJECT_SOURCE_DIR}/externals/glew-2.1.0/include
)

target_link_libraries(engine
		glfw
    	${OPENGL_gl_LIBRARY})


target_compile_features(engine PRIVATE cxx_lambda_init_captures)

enable_testing()
add_subdirectory(test)

add_subdirectory(examples)
