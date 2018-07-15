#include "glslShaderCompiler.h"
#include <GL/glew.h>
#include <iostream>

namespace Fire
{

namespace
{
bool CompileError(GLuint shaderID)
{
    GLint isCompiled = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        GLchar* errorLog = new GLchar[maxLength + 1];
        glGetShaderInfoLog(shaderID, maxLength, &maxLength, errorLog);

        std::cout << errorLog << std::endl;

        glDeleteShader(shaderID); // Don't leak the shader.
        delete[] errorLog;

        return false;
    }

    return true;
}

GLenum MapShaderType(ShaderCompiler::ShaderType shaderType)
{
    switch(shaderType)
    {
    case ShaderCompiler::ShaderType::VERTEX_SHADER:
        return GL_VERTEX_SHADER;
    case ShaderCompiler::ShaderType::FRAGMENT_SHADER:
        return GL_FRAGMENT_SHADER;
    default:
        return GL_NONE;
    };
}
} // namespace

GLSLShaderCompiler::GLSLShaderCompiler(
    std::string const& code, ShaderType shaderType)
    : m_code(code)
    , m_shaderType(shaderType)
{
}

int GLSLShaderCompiler::Compile()
{
    auto shaderID = glCreateShader(MapShaderType(m_shaderType));
    auto source = m_code.c_str();
    glShaderSource(shaderID, 1, &source, nullptr);
    glCompileShader(shaderID);
    if(CompileError(shaderID))
    {
        exit(EXIT_FAILURE);
    }

    return shaderID;
}

} // namespace Fire
