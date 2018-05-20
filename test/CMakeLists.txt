include_directories(
  ${gtest_SOURCE_DIR}/include
  ../include
)

set(test_sources
  ./findByNameTest.cpp
  ./sceneTest.cpp
  ./windowTest.cpp
  ./renderableTest.cpp
  ./rendererTest.cpp
  ./vertexDataTest.cpp
  ./materialTest.cpp
  ./textureBinderTest.cpp
  ./shaderTest.cpp
)

add_executable(engine_tests ${test_sources})

if (MSVC)
  target_compile_options(engine_tests PUBLIC /W4)
else()
  target_compile_options(engine_tests PUBLIC -Wall -Wextra -Wpedantic -std=c++17)
endif()

target_compile_features(engine_tests PRIVATE cxx_lambda_init_captures)

target_link_libraries(engine_tests gtest_main engine gmock)

add_custom_command (
  TARGET engine_tests POST_BUILD
  COMMAND engine_tests --gtest_output=xml:engine_tests.xml
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}
)
