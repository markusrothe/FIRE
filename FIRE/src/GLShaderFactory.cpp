#include "GLShaderFactory.h"
#include <glad/glad.h>

#include <GLFW/glfw3.h>
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
} // namespace
unsigned int GLShaderFactory::CreateDefaultShader()
{
    std::string const vsCode =
        "#version 440\n"
        "layout(location = 0) in vec3 vPos;\n"
        "uniform mat4 MVP;\n"
        "out vec3 posVS;\n"
        "void main() { \n"
        "    gl_Position = MVP * vec4(vPos.xyz, 1.0);\n"
        "    posVS = vPos;\n"
        "}\n";

    std::string const fsCode =
        "#version 440\n"
        "in vec3 posVS;\n"
        "out vec4 color;\n"
        "void main() { color = vec4(0.4,0.4,0.4,1.0) + vec4(posVS.xyz, 1.0); }\n";

    auto vertexShader = CompileShader(GL_VERTEX_SHADER, vsCode);
    auto fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fsCode);

    auto shader = glCreateProgram();
    glAttachShader(shader, vertexShader);
    glAttachShader(shader, fragmentShader);

    glBindAttribLocation(shader, 0, "vPos");
    glLinkProgram(shader);
    if(LinkError(shader))
    {
        exit(EXIT_FAILURE);
    }

    return shader;
}

unsigned int GLShaderFactory::Create(std::vector<std::pair<ShaderType, std::string>> const& /*shaderCode*/)
{
    return CreateDefaultShader();
}

} // namespace FIRE
