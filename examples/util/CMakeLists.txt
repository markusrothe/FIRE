add_library(util STATIC
    ./FPSOverlay.h
    ./InputMapping.h
    ./InputMapping.cpp
    )

target_include_directories(util
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    )

target_link_libraries(util
    PUBLIC
    FIRE::FIRE
    FIRE::CompileOptions
    )