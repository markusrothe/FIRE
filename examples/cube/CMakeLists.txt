add_executable(cube
    main.cpp
)

target_link_libraries(cube
    PRIVATE
        FIRE
)

install(
    TARGETS cube
    DESTINATION bin
)

install(
    FILES $<TARGET_FILE:FIRE>
    DESTINATION bin
)
