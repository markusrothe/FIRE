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

if(MSVC)
    target_compile_options(cube PRIVATE /W4 /WX)
else()
    target_compile_options(cube PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
set_property(TARGET cube PROPERTY CXX_STANDARD 17)