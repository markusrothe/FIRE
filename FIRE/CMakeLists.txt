add_library(FIRE STATIC
    include/FIRE/Window.h
    include/FIRE/RenderContext.h        
    include/FIRE/Mesh.h
    include/FIRE/Renderable.h  
    include/FIRE/Renderer.h 
    include/FIRE/Vertex.h
    include/FIRE/VertexDeclaration.h
    include/FIRE/GLFactory.h
    
    src/glad/include/glad/glad.h
    src/glad/include/KHR/khrplatform.h
    src/Uploader.h
    src/DrawAgent.h
    src/GLUploader.h    
    src/GLDrawAgent.h
    src/GLRenderContext.h
    src/RendererImpl.h
    src/MaterialManager.h
    
    src/glad/src/glad.c
    src/Window.cpp    
    src/Renderable.cpp
    src/Mesh.cpp
    src/GLFactory.cpp
    src/GLUploader.cpp
    src/GLDrawAgent.cpp
    src/GLRenderContext.cpp    
    src/RendererImpl.cpp
    src/MaterialManager.cpp
    src/VertexDeclaration.cpp
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
