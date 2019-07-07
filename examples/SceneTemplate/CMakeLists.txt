add_library(SceneTemplate STATIC
    ./include/SceneTemplate/Input.h
    ./include/SceneTemplate/SceneTemplate.h
    
    ./src/Input.cpp
    ./src/SceneTemplate.cpp
)

target_include_directories(SceneTemplate
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(SceneTemplate
    PUBLIC
    FIRE
    CompileOptions
)
