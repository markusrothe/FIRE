if (NOT BUILD_TESTING)
    return()
endif ()

add_executable(FIRE_tests
    ./Utilities.h

    ./CameraComponentTest.cpp
    ./RenderingComponentTest.cpp
    ./WindowTest.cpp
    ./MeshTest.cpp
    ./MaterialFactoryTest.cpp
    ./MaterialTest.cpp
    ./SceneTest.cpp
    ./SceneObjectTest.cpp
    ./TransformTest.cpp
    ./InputListenerTest.cpp
    ./MeshManagerTest.cpp
    ./TextureFactoryTest.cpp
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
    MeasureCoverage
    assimp::assimp
    glad
    )

include(GoogleTest)
gtest_discover_tests(FIRE_tests)

add_custom_command(
    TARGET FIRE_tests POST_BUILD
    COMMAND ctest --output-on-failure -C $<CONFIGURATION>
)

install(
    TARGETS FIRE_tests
    DESTINATION bin
)

install(
    FILES
    $<TARGET_FILE:assimp::assimp>
    DESTINATION bin
)

