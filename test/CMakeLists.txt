include_directories(
  ${gtest_SOURCE_DIR}/include
  ../include
)

set(test_sources 
  ./vertexDeclarationTest.cpp
  ./transformTest.cpp
  ./tokenizeTest.cpp
  ./entityTest.cpp
  ./fontManagerTest.cpp
  ./keyHandlerListenerTest.cpp
  ./keyHandlerTest.cpp
  ./materialConfigTest.cpp
  ./materialManagerTest.cpp
  ./materialMapTest.cpp
  ./meshTest.cpp
  ./meshUtilitiesTest.cpp
  ./renderableManagerTest.cpp
  ./renderableTest.cpp
  ./sceneManagerTest.cpp
  ./sceneTest.cpp
  ./shaderTest.cpp
  ./tokenizeTest.cpp
  ./transformTest.cpp
  ./vertexDeclarationTest.cpp
  ./windowTest.cpp
)

add_executable(engine_tests ${test_sources})

target_link_libraries(engine_tests gtest_main engine)

add_custom_command (
  TARGET engine_tests POST_BUILD
  COMMAND engine_tests --gtest_output=xml:engine_tests.xml
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}
)
