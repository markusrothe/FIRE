set(src_files
  ./src/main.cpp
)

add_executable(simple_example ${src_files} ${glew_header} ${glew_source})

find_package(OpenGL REQUIRED)

target_include_directories(simple_example PUBLIC
  ${PROJECT_SOURCE_DIR}/include
  )

target_link_libraries(simple_example
    engine
    ${OPENGL_gl_LIBRARY}
    glfw)

target_compile_features(simple_example PRIVATE cxx_lambda_init_captures)
