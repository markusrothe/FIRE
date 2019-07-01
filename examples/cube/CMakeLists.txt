add_executable(cube
    CubeSceneComponent.h
    CubeSceneComponent.cpp
    main.cpp
)

target_link_libraries(cube
    PRIVATE
    FIRE
    SceneTemplate
    CompileOptions
)

install(
    TARGETS cube
    DESTINATION bin
)

