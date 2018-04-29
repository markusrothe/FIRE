set(header_files
)

set(src_files
  ./src/main.cpp
)

add_executable(simple_example ${src_files} ${header_files})

find_package(OpenGL REQUIRED)

target_include_directories(simple_example PUBLIC
  ../../include
  )

target_link_libraries(simple_example engine)

target_compile_features(simple_example PRIVATE cxx_lambda_init_captures)
