cmake_minimum_required(VERSION 3.0)

project(engine)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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
  ${src_files} ${header_files}
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

find_package(OpenGL REQUIRED)

target_include_directories (engine SYSTEM PUBLIC
  ${OPENGL_INCLUDE_DIR} 
  ${PROJECT_SOURCE_DIR}/contrib/stb_image
  ${PROJECT_SOURCE_DIR}/contrib/glm-0.9.9-a2
  ${PROJECT_SOURCE_DIR}/contrib/glfw-3.2.1/include
  ${PROJECT_SOURCE_DIR}/contrib/glew-2.1.0/include  
)

if(MSVC)
    find_library(GLEW NAMES glew32s HINTS ${PROJECT_SOURCE_DIR}/contrib/glew-2.1.0/lib/Release/Win32)    
    find_library(GLFW_d NAMES glfw3 HINTS ${PROJECT_SOURCE_DIR}/contrib/glfw-3.2.1/msvc_19_0/debug)    
    find_library(GTEST_d NAMES gtestd HINTS ${PROJECT_SOURCE_DIR}/contrib/gtest/googletest/msvc_19_0/debug)
    find_library(GTEST_MAIN_d NAMES gtest_maind HINTS ${PROJECT_SOURCE_DIR}/contrib/gtest/googletest/msvc_19_0/debug)
    find_library(GMOCK_d NAMES gmockd HINTS ${PROJECT_SOURCE_DIR}/contrib/gtest/googlemock/msvc_19_0/debug)
    
    find_library(GLFW NAMES glfw3 HINTS ${PROJECT_SOURCE_DIR}/contrib/glfw-3.2.1/msvc_19_0/release)
    find_library(GTEST NAMES gtest HINTS ${PROJECT_SOURCE_DIR}/contrib/gtest/googletest/msvc_19_0/release)
    find_library(GTEST_MAIN NAMES gtest_main HINTS ${PROJECT_SOURCE_DIR}/contrib/gtest/googletest/msvc_19_0/release)
    find_library(GMOCK NAMES gmock HINTS ${PROJECT_SOURCE_DIR}/contrib/gtest/googlemock/msvc_19_0/release)

	target_link_libraries(engine
		${GLEW}
    	${OPENGL_gl_LIBRARY}
    	debug ${GLFW_d} optimized ${GLFW})
else()
    find_library(GLEW NAMES libGLEW.a HINTS ${PROJECT_SOURCE_DIR}/contrib/glew-2.1.0/lib/Release/gcc-7.3)    

	find_package(glfw3 3.2 REQUIRED)

    find_library(GTEST NAMES libgtest.a HINTS ${PROJECT_SOURCE_DIR}/contrib/gtest/googletest/gcc-7.3)
    find_library(GTEST_MAIN NAMES libgtest_main.a HINTS ${PROJECT_SOURCE_DIR}/contrib/gtest/googletest/gcc-7.3)
    find_library(GMOCK NAMES libgmock.a HINTS ${PROJECT_SOURCE_DIR}/contrib/gtest/googlemock/gcc-7.3)

	target_link_libraries(engine
		${GLEW}
    	${OPENGL_gl_LIBRARY}
		glfw)
endif()

target_compile_features(engine PRIVATE cxx_lambda_init_captures)

enable_testing()
add_subdirectory(test)

add_subdirectory(examples)
