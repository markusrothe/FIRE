#include "shader.h"
#include <fstream>
#include <iostream>

namespace blocks
{
    namespace
    {
        bool CheckForCompileError(GLuint shader)
        {
            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if (isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                // The maxLength includes the NULL character
                GLchar* errorLog = new GLchar[maxLength + 1];
                glGetShaderInfoLog(shader, maxLength, &maxLength, errorLog);

                std::cout << errorLog << std::endl;

                glDeleteShader(shader); // Don't leak the shader.
                delete[] errorLog;

                return false;
            }

            return true;
        }
    }

    Shader::Shader(std::string const code, GLenum shaderType)
    {
        m_programID = glCreateShader(shaderType);

        char const* s = code.c_str();
        glShaderSource(m_programID, 1, &s, NULL);
        glCompileShader(m_programID);
        if (!CheckForCompileError(m_programID))
        {
            exit(EXIT_FAILURE);
        }
    }

    std::unique_ptr<Shader> CreateShaderFromFile(std::string const filepath, GLenum shaderType)
    {
        std::ifstream shaderFile(filepath);
        std::string shaderCode((std::istreambuf_iterator<char>(shaderFile))
            , std::istreambuf_iterator<char>());

        return std::make_unique<Shader>(shaderCode, shaderType);
    }
}
