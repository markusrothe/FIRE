add_executable(example1
    main.cpp
)

target_link_libraries(example1
    PRIVATE
        FIRE
)

install(
    TARGETS
        example1
    DESTINATION 
        "bin"
)

install(
    FILES
        $<TARGET_FILE:FIRE>
    DESTINATION
        bin
)
