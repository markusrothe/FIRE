add_executable(cube
    src/main.cpp
)

target_include_directories(cube
PRIVATE
    src
)

target_link_libraries(cube
    PRIVATE
    FIRE
    FIRE::exampleComponents
    FIRE::CompileOptions
)

install(
    TARGETS cube
    DESTINATION bin/cube
)

install(
    FILES $<TARGET_PROPERTY:FIRE,RESOURCE>
    DESTINATION bin/cube
)