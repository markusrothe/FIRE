add_library(FIRE STATIC
    include/FIRE/Window.h
    include/FIRE/RenderContext.h
    include/FIRE/MeshManager.h
    include/FIRE/Mesh3D.h
    include/FIRE/Renderable.h
    include/FIRE/VertexDeclaration.h
    include/FIRE/GLFactory.h
    include/FIRE/Component.h
    include/FIRE/RenderingComponent.h
    include/FIRE/LightComponent.h
    include/FIRE/CameraComponent.h
    include/FIRE/InputComponent.h
    include/FIRE/Scene.h
    include/FIRE/SceneObject.h
    include/FIRE/Transform.h
    include/FIRE/InputListener.h
    include/FIRE/Key.h
    include/FIRE/MouseKey.h
    include/FIRE/KeyAction.h
    include/FIRE/ShaderFactory.h
    include/FIRE/ShaderType.h
    include/FIRE/MaterialFactory.h
    include/FIRE/Material.h
    include/FIRE/glmfwd.h
    include/FIRE/MeshType.h
    include/FIRE/TextOverlay.h
    include/FIRE/Message.h
    include/FIRE/Noise.h
    include/FIRE/MainLoop.h
    include/FIRE/Texture.h

    src/GLShaderFactory.h
    src/GLRenderContext.h
    include/FIRE/Renderer.h
    src/TextureFactory.h
    src/FontTextureFactory.h
    src/GLFontTextureFactory.h
    src/ImageTextureFactory.h
    src/GLImageTextureFactory.h

    src/Window.cpp
    src/Renderable.cpp
    src/Mesh3D.cpp
    src/GLFactory.cpp
    src/GLShaderFactory.cpp
    src/GLRenderContext.cpp
    src/Renderer.cpp
    src/MaterialFactory.cpp
    src/VertexDeclaration.cpp
    src/Scene.cpp
    src/SceneObject.cpp
    src/RenderingComponent.cpp
    src/CameraComponent.cpp
    src/LightComponent.cpp
    src/InputComponent.cpp
    src/Transform.cpp
    src/InputListener.cpp
    src/Material.cpp
    src/MeshManager.cpp
    src/TextOverlay.cpp
    src/TextureFactory.cpp
    src/GLFontTextureFactory.cpp
    src/Noise.cpp
    src/MainLoop.cpp
    src/Texture.cpp
    src/GLImageTextureFactory.cpp src/MaterialBinder.h src/GLVertexLayout.cpp src/GLVertexLayout.h src/VertexLayoutFactory.h src/GLVertexLayoutFactory.cpp src/GLVertexLayoutFactory.h src/GLMaterialBinder.cpp src/GLMaterialBinder.h src/Draw.h src/GLDraw.cpp src/GLDraw.h src/VertexLayout.h)

target_include_directories(FIRE
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE
    src
    )

target_link_libraries(FIRE
    PUBLIC
    glm

    PRIVATE
    glfw
    glad
    CompileOptions
    MeasureCoverage
    freetype
    FastNoise
    assimp::assimp
    )

if (MSVC)
    set_target_properties(FIRE PROPERTIES COMPILE_FLAGS /D_USE_MATH_DEFINES)
endif ()

file(GLOB_RECURSE assets ${CMAKE_CURRENT_SOURCE_DIR}/assets/*)
set_target_properties(FIRE
    PROPERTIES
    RESOURCE "${assets}"
    )

add_subdirectory(test)
