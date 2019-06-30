#include "GLShaderFactory.h"
#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <cassert>
#include <iostream>
#include <vector>
namespace FIRE
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

        return true;
    }

    return false;
}
bool LinkError(GLuint program)
{
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
    if(isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

        // The program is useless now. So delete it.
        glDeleteProgram(program);

        return true;
    }
    return false;
}
GLuint CompileShader(GLenum shaderType, std::string const& code)
{
    auto shaderID = glCreateShader(shaderType);
    auto vertexSource = code.c_str();
    glShaderSource(shaderID, 1, &vertexSource, nullptr);
    glCompileShader(shaderID);

    if(CompileError(shaderID))
    {
        exit(EXIT_FAILURE);
    }

    return shaderID;
}

GLenum ToGLShaderType(ShaderType shaderType)
{
    switch(shaderType)
    {
    case ShaderType::VERTEX_SHADER:
        return GL_VERTEX_SHADER;
    case ShaderType::FRAGMENT_SHADER:
        return GL_FRAGMENT_SHADER;
    default:
        assert(false);
        return GL_VERTEX_SHADER;
    }
}
} // namespace
unsigned int GLShaderFactory::CreateDefaultShader()
{
    std::string const vsCode =
        "#version 440\n"
        "layout(location = 0) in vec3 vPos;"
        "uniform mat4 MVP;"
        "out vec3 posVS;"
        "void main() {"
        "    gl_Position = MVP * vec4(vPos.xyz, 1.0);"
        "    posVS = vPos;"
        "}";

    std::string const fsCode =
        "#version 440\n"
        "in vec3 posVS;"
        "out vec4 color;"
        "void main() { color = vec4(1.0 , 1.0 , 1.0, 1.0);}";

    std::vector<std::pair<ShaderType, std::string>> shaders = {
        {ShaderType::VERTEX_SHADER, vsCode},
        {ShaderType::FRAGMENT_SHADER, fsCode}};

    return Create(shaders);
}

unsigned int GLShaderFactory::Create(std::vector<std::pair<ShaderType, std::string>> const& shaderCode)
{
    auto shaderProgram = glCreateProgram();

    for(auto const& shaderSource : shaderCode)
    {
        auto const shaderType = ToGLShaderType(shaderSource.first);

        glAttachShader(shaderProgram, CompileShader(shaderType, shaderSource.second));
    }

    glBindAttribLocation(shaderProgram, 0, "vPos");
    glLinkProgram(shaderProgram);
    if(LinkError(shaderProgram))
    {
        exit(EXIT_FAILURE);
    }

    return shaderProgram;
}

} // namespace FIRE
