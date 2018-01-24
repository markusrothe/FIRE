#ifndef shader_h
#define shader_h

#include <GL/glew.h>
#include <string>
#include <memory>

namespace blocks
{
    class Shader
    {
    public:        
        Shader(std::string const code, GLenum shaderType);

        GLuint GetID() const { return m_programID; }
        
    private:
        GLuint m_programID;
    };
    
    std::unique_ptr<Shader> CreateShaderFromFile(std::string const filepath, GLenum shaderType);
    
}

#endif // shader_h
