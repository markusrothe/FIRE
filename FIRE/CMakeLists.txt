
add_subdirectory(src/glm EXCLUDE_FROM_ALL)
add_library(FIRE STATIC
    include/FIRE/Camera.h
    include/FIRE/Window.h
    include/FIRE/RenderContext.h        
    include/FIRE/Mesh.h
    include/FIRE/Renderable.h  
    include/FIRE/Renderer.h 
    include/FIRE/Vector.h
    include/FIRE/Matrix.h
    include/FIRE/VertexDeclaration.h
    include/FIRE/GLFactory.h
    include/FIRE/Scene.h
    include/FIRE/Transform.h
    include/FIRE/InputListener.h
    include/FIRE/Key.h
    include/FIRE/MouseKey.h
    include/FIRE/KeyAction.h
    include/FIRE/ShaderFactory.h
    include/FIRE/ShaderType.h
    include/FIRE/MaterialFactory.h
    include/FIRE/Material.h
    
    src/glad/include/glad/glad.h
    src/glad/include/KHR/khrplatform.h
    src/glm_wrapper.h
    src/Uploader.h
    src/DrawAgent.h
    src/GLUploader.h    
    src/GLDrawAgent.h
    src/GLShaderFactory.h
    src/GLRenderContext.h
    src/RendererImpl.h

        
    src/glad/src/glad.c
    src/Camera.cpp
    src/Window.cpp    
    src/Renderable.cpp
    src/Mesh.cpp
    src/GLFactory.cpp
    src/GLUploader.cpp
    src/GLDrawAgent.cpp
    src/GLShaderFactory.cpp
    src/GLRenderContext.cpp    
    src/RendererImpl.cpp
    src/MaterialFactory.cpp
    src/VertexDeclaration.cpp
    src/Matrix.cpp
    src/Scene.cpp
    src/Transform.cpp
    src/InputListener.cpp
    src/Material.cpp
)

target_include_directories(FIRE
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
PRIVATE
    src
    src/glad/include
)

target_link_libraries(FIRE
PRIVATE
    glfw
    glm
    CompileOptions
)

add_subdirectory(test)
