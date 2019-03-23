#include "MaterialManager.h"
#include <iostream>
#include <tuple>
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

std::pair<std::string, GLuint> CreateDefaultMaterial()
{
    std::string const vsCode =
        "#version 440\n"
        "layout(location = 0) in vec3 vPos;\n"
        "void main() { gl_Position = vec4(vPos.xyz, 1.0); }\n";

    std::string const fsCode =
        "#version 440\n"
        "out vec4 color;\n"
        "void main() { color = vec4(1.0, 1.0, 1.0, 1.0); }\n";

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

    return std::make_pair("Default", shader);
}
} // namespace

MaterialManager::MaterialManager()
{
    m_shaders.insert(CreateDefaultMaterial());
}

GLuint MaterialManager::GetShader(std::string const& materialName) const
{
    auto const shader = m_shaders.find(materialName);
    return (shader != m_shaders.end()) ? shader->second : 0u;
}
} // namespace FIRE
