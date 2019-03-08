add_library(FIRE STATIC
    include/FIRE/FIRE.h
    src/FIRE.cpp
)

target_include_directories(FIRE
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> 
    $<INSTALL_INTERFACE:include> 
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND COVERAGE)
    target_compile_options(FIRE PUBLIC --coverage)
    target_link_libraries(FIRE --coverage)
endif()

add_subdirectory(test)