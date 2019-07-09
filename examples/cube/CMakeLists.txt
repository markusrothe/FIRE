add_executable(cube
    CubeRenderingComponent.h
    CubeCameraComponent.h
    CubeLightComponent.h    
    CubeRenderingComponent.cpp
    CubeCameraComponent.cpp
    CubeLightComponent.cpp
    main.cpp
)

target_link_libraries(cube
    PRIVATE
    FIRE
    CompileOptions
)

install(
    TARGETS cube
    DESTINATION bin
)

install(
    FILES $<TARGET_PROPERTY:FIRE,RESOURCE>
    DESTINATION bin
)