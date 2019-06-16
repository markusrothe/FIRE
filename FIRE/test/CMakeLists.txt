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
        CompileOptions
)

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
