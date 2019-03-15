add_library(FIRE STATIC
    include/FIRE/FIRE.h
    src/FIRE.cpp
)

target_include_directories(FIRE
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if(MSVC)
    target_compile_options(FIRE PRIVATE /W4 /WX)
else()
    target_compile_options(FIRE PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" AND COVERAGE)
    target_compile_options(FIRE PUBLIC --coverage)
    target_link_libraries(FIRE PUBLIC --coverage)
endif()

add_subdirectory(test)
