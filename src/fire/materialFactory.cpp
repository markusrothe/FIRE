#include "materialFactory.h"
#include "material.h"

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
} // namespace

std::unique_ptr<Material> CreateMaterial(
    std::string const& materialName, std::string const& vertexShaderCode,
    std::string const& fragmentShaderCode)
{
    auto vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderCode);
    auto fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderCode);

    auto shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    return std::make_unique<Material>(materialName, shaderProgram);
}

} // namespace Fire
