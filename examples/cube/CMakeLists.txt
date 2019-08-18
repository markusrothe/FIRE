add_executable(cube
    src/main.cpp
    )

target_include_directories(cube
    PRIVATE
    src
    )

target_link_libraries(cube
    PRIVATE
    FIRE::FIRE
    FIRE::CompileOptions
    util
    )

install(
    TARGETS cube
    DESTINATION bin/cube
)

install(
    FILES $<TARGET_PROPERTY:FIRE,RESOURCE>
    DESTINATION bin/cube
)