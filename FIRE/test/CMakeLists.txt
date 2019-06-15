if(NOT BUILD_TESTING)
    return()
endif()

add_executable(FIRE_tests
    ./WindowTest.cpp
    ./RenderableTest.cpp
    ./RendererTest.cpp
    ./MeshTest.cpp
    ./MaterialFactoryTest.cpp
    ./MaterialTest.cpp
    ./CameraTest.cpp
    ./MatrixTest.cpp
    ./SceneTest.cpp
    ./TransformTest.cpp
    ./InputListenerTest.cpp
)

target_include_directories(FIRE_tests
    PUBLIC
        $<TARGET_PROPERTY:FIRE,INCLUDE_DIRECTORIES>
        $<TARGET_PROPERTY:FIRE,INTERFACE_INCLUDE_DIRECTORIES>
)

target_link_libraries(FIRE_tests
    PRIVATE
        FIRE
        gtest
        gtest_main
        gmock
)

if(MSVC)
    string(REGEX REPLACE " /W[0-4]" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
    string(REGEX REPLACE " /W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    target_compile_options(FIRE_tests PRIVATE /W4 /WX /std:c++17)
else()
    target_compile_options(FIRE_tests PRIVATE -Wall -Wextra -pedantic -Werror)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" AND COVERAGE)
    target_compile_options(FIRE_tests PUBLIC --coverage)
    target_link_libraries(FIRE_tests PUBLIC --coverage)
endif()

include(GoogleTest)
gtest_discover_tests(FIRE_tests)

add_custom_command(
    TARGET FIRE_tests POST_BUILD                   
    COMMAND ctest -C $<CONFIGURATION> --output-on-failure
)

install(
    TARGETS FIRE_tests
    DESTINATION bin
)

install(
    FILES $<TARGET_FILE:FIRE>
    DESTINATION bin
)
