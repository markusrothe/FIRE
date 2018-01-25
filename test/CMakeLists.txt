include_directories(
  ${gtest_SOURCE_DIR}/include
  ../include
)

set(test_sources 
    ./vertexDeclarationTest.cpp
)

add_executable(engine_tests ${test_sources})

target_link_libraries(engine_tests gtest_main engine)

add_custom_command (
  TARGET engine_tests POST_BUILD
  COMMAND engine_tests --gtest_output=xml:engine_tests.xml
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}
)