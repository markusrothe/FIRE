
add_subdirectory(src/glm)
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
    
    src/glad/include/glad/glad.h
    src/glad/include/KHR/khrplatform.h
    src/glm_wrapper.h
    src/Uploader.h
    src/DrawAgent.h
    src/ShaderFactory.h
    src/GLUploader.h    
    src/GLDrawAgent.h
    src/GLShaderFactory.h
    src/GLRenderContext.h
    src/RendererImpl.h
    src/MaterialManager.h
        
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
    src/MaterialManager.cpp
    src/VertexDeclaration.cpp
    src/Matrix.cpp
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
)

if(MSVC)
    string(REGEX REPLACE " /W[0-4]" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
    string(REGEX REPLACE " /W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    target_compile_options(FIRE PRIVATE /W4 /WX /std:c++17)
else()
    target_compile_options(FIRE PRIVATE -Wall -Wextra -pedantic -Werror)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" AND COVERAGE)
    target_compile_options(FIRE PUBLIC --coverage)
    target_link_libraries(FIRE PUBLIC --coverage)
endif()

add_subdirectory(test)
