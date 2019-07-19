add_library(FastNoise
    ./include/FastNoise/FastNoise.h
    ./src/FastNoise.cpp
)

target_include_directories(FastNoise
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
PRIVATE
    src
)
