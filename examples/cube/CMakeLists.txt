add_executable(cube
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

