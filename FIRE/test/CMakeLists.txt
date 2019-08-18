if(NOT BUILD_TESTING)
    return()
endif()

add_executable(FIRE_tests
    FIRE_tests/Utilities.h
    FIRE_tests/CameraComponentTest.cpp
    FIRE_tests/RenderingComponentTest.cpp
    FIRE_tests/WindowTest.cpp
    FIRE_tests/MeshTest.cpp
    FIRE_tests/MaterialTest.cpp
    FIRE_tests/SceneTest.cpp
    FIRE_tests/SceneObjectTest.cpp
    FIRE_tests/TransformTest.cpp
    FIRE_tests/InputListenerTest.cpp
    FIRE_tests/MeshManagerTest.cpp
    FIRE_tests/RendererTest.cpp
    FIRE_tests/Mocks/TextureFactoryMock.h
    FIRE_tests/Mocks/Texture2DMock.h
    FIRE_tests/RenderableTest.cpp
    FIRE_tests/ModelLoaderTest.cpp
    FIRE_tests/AssetFacadeTest.cpp FIRE_tests/Stubs/Texture2DStub.h FIRE_tests/Mocks/ShaderFactoryMock.h FIRE_tests/Stubs/CubeOBJ.h FIRE_tests/Stubs/CubeOBJ.cpp FIRE_tests/Mocks/MaterialBinderMock.h FIRE_tests/Mocks/DrawMock.h FIRE_tests/Mocks/VertexLayoutFactoryMock.h FIRE_tests/Stubs/VertexLayoutStub.h FIRE_tests/Mocks/ComponentStub.h FIRE_tests/RenderableBuilderTest.cpp FIRE_tests/OverlayBuilderTest.cpp)

target_include_directories(FIRE_tests
    PUBLIC
    $<TARGET_PROPERTY:FIRE,INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:FIRE,INTERFACE_INCLUDE_DIRECTORIES>
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/FIRE_tests/Mocks
    ${CMAKE_CURRENT_SOURCE_DIR}/FIRE_tests/Stubs

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

