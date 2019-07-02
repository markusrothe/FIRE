add_library(FIRE STATIC
    include/FIRE/Camera.h
    include/FIRE/Window.h
    include/FIRE/RenderContext.h
    include/FIRE/MeshManager.h
    include/FIRE/Mesh3D.h
    include/FIRE/Mesh2D.h
    include/FIRE/Renderable.h  
    include/FIRE/Renderer.h 
    include/FIRE/VertexDeclaration.h
    include/FIRE/GLFactory.h
    include/FIRE/Scene.h
    include/FIRE/SceneComponent.h
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
    
    src/Uploader.h
    src/DrawAgent.h
    src/GLUploader.h    
    src/GLDrawAgent.h
    src/GLShaderFactory.h
    src/GLRenderContext.h
    src/RendererImpl.h
      
    src/Camera.cpp
    src/Window.cpp    
    src/Renderable.cpp
    src/Mesh3D.cpp
    src/Mesh2D.cpp
    src/GLFactory.cpp
    src/GLUploader.cpp
    src/GLDrawAgent.cpp
    src/GLShaderFactory.cpp
    src/GLRenderContext.cpp    
    src/RendererImpl.cpp
    src/MaterialFactory.cpp
    src/VertexDeclaration.cpp
    src/Scene.cpp
    src/Transform.cpp
    src/InputListener.cpp
    src/Material.cpp
    src/MeshManager.cpp
)

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
)

if(MSVC)
    set_target_properties(FIRE PROPERTIES COMPILE_FLAGS /D_USE_MATH_DEFINES)
endif()


add_subdirectory(test)
