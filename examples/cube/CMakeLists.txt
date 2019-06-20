add_executable(cube
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
    FILES 
    $<TARGET_FILE:FIRE>
    ${CMAKE_CURRENT_SOURCE_DIR}/PhongVS.glsl
    ${CMAKE_CURRENT_SOURCE_DIR}/PhongFS.glsl
    DESTINATION bin
)