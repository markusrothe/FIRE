add_library(FIRE STATIC
    include/FIRE/AssetFacade.h
    include/FIRE/Window.h
    include/FIRE/RenderContext.h
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
    src/InputListener.h
    include/FIRE/Key.h
    include/FIRE/MouseKey.h
    include/FIRE/KeyAction.h
    include/FIRE/ShaderType.h
    include/FIRE/Material.h
    include/FIRE/glmfwd.h
    include/FIRE/MeshType.h
    include/FIRE/TextOverlay.h
    include/FIRE/Message.h
    include/FIRE/Noise.h
    include/FIRE/MainLoop.h
    include/FIRE/Texture2D.h
    include/FIRE/Renderer.h
    include/FIRE/RenderableBuilder.h
    include/FIRE/OverlayBuilder.h

    src/ShaderFactory.h
    src/GLShaderFactory.h
    src/GLRenderContext.h
    src/GLMaterialBinder.h
    src/Draw.h
    src/MaterialBinder.h
    src/GLVertexLayout.h
    src/VertexLayoutFactory.h
    src/GLVertexLayoutFactory.h
    src/GLDraw.h
    src/VertexLayout.h
    src/TextureFactory.h
    src/GLTextureFactory.h
    src/GLTexture2D.h
    src/MeshFactory.h
    src/ModelLoader.h
    src/ModelLoader.cpp
    src/Window.cpp
    src/Renderable.cpp
    src/Mesh3D.cpp
    src/GLFactory.cpp
    src/GLShaderFactory.cpp
    src/GLRenderContext.cpp
    src/Renderer.cpp
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
    src/MeshFactory.cpp
    src/TextOverlay.cpp
    src/Noise.cpp
    src/MainLoop.cpp
    src/GLTexture2D.cpp
    src/GLVertexLayout.cpp
    src/GLVertexLayoutFactory.cpp
    src/GLMaterialBinder.cpp
    src/GLDraw.cpp
    src/GLTextureFactory.cpp
    src/AssetFacade.cpp
    src/RenderableBuilder.cpp
    src/OverlayBuilder.cpp include/FIRE/RenderableSubmitter.h include/FIRE/OverlayComponent.h src/OverlayComponent.cpp include/FIRE/OverlaySubmitter.h)

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
    stb_image
    )

if(MSVC)
    set_target_properties(FIRE PROPERTIES COMPILE_FLAGS /D_USE_MATH_DEFINES)
endif()

file(GLOB_RECURSE assets ${CMAKE_CURRENT_SOURCE_DIR}/assets/*)
set_target_properties(FIRE
    PROPERTIES
    RESOURCE "${assets}"
    )

add_subdirectory(test)
