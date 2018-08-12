include_directories(
  ${PROJECT_SOURCE_DIR}/contrib/gtest/googletest/include
  ${PROJECT_SOURCE_DIR}/contrib/gtest/googlemock/include
  ${PROJECT_SOURCE_DIR}/include
)

set(test_sources
  ./findByNameTest.cpp
  ./sceneTest.cpp
  ./windowTest.cpp
  ./renderableTest.cpp
  ./rendererTest.cpp
  ./vertexDataTest.cpp
  ./indexDataTest.cpp
  ./materialTest.cpp
  ./shaderParserTest.cpp
)

add_executable(engine_tests ${test_sources})

if (MSVC)
  target_compile_options(engine_tests PUBLIC /W4)
else()
  if (COVERAGE)
    target_compile_options(engine_tests PUBLIC --coverage)
    target_link_libraries(engine_tests --coverage)
  endif()
  
  target_compile_options(engine_tests PUBLIC -Wall -Wextra -Wpedantic -std=c++17)
endif()

target_compile_features(engine_tests PRIVATE cxx_lambda_init_captures)

target_link_libraries(engine_tests
    engine
    ${GLEW}
    debug ${GTEST_d} optimized ${GTEST}
    debug ${GTEST_MAIN_d} optimized ${GTEST_MAIN}
    debug ${GMOCK_d} optimized ${GMOCK})

add_custom_command (
  TARGET engine_tests POST_BUILD
  COMMAND engine_tests --gtest_output=xml:engine_tests.xml
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}
)
