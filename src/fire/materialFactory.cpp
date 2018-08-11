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

    glBindAttribLocation(shaderProgram, 0, "vertex");

    glLinkProgram(shaderProgram);

    if(LinkError(shaderProgram))
    {
        exit(EXIT_FAILURE);
    }

    return std::make_unique<Material>(materialName, shaderProgram);
}

std::unique_ptr<Material> CreateDefaultMaterial()
{
    std::string const vsCode =
        "#version 440\n"
        "layout(location = 0) in vec3 vertex;\n"
        "void main() { gl_Position = vec4(vertex.xyz, 1.0); }\n";

    std::string const fsCode =
        "#version 440\n"
        "out vec4 color;\n"
        "void main() { color = vec4(1.0, 1.0, 1.0, 1.0); }\n";

    return CreateMaterial("default", vsCode, fsCode);
}

} // namespace Fire
