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
    string(REGEX REPLACE " /W[0-4]" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
    string(REGEX REPLACE " /W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    target_compile_options(cube PRIVATE /W4 /WX /std:c++17)
else()
    target_compile_options(cube PRIVATE -Wall -Wextra -pedantic -Werror)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
endif()