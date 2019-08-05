add_library(exampleComponents STATIC
    include/Mesh3DRenderingComponent.h
    include/PerspectiveCameraComponent.h
    include/PointLightComponent.h    
    include/FPSOverlayComponent.h
    include/InputMappingComponent.h

    src/Mesh3DRenderingComponent.cpp
    src/PerspectiveCameraComponent.cpp
    src/PointLightComponent.cpp
    src/FPSOverlayComponent.cpp
    src/InputMappingComponent.cpp
)
add_library(FIRE::exampleComponents ALIAS exampleComponents)

target_include_directories(exampleComponents
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
PRIVATE
    src
)

target_link_libraries(exampleComponents
    PRIVATE
    FIRE
    FIRE::CompileOptions
)