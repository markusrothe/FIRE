#include "compileMaterial.h"
#include "shader.h"
#include <memory>
#include <iostream>
#include <GL/glew.h>

namespace blocks
{
    MaterialMapEntry CompileMaterial(MaterialConfig const& config)
    {
        std::unique_ptr<Shader> vertexShader = CreateShaderFromFile(config.m_vertexShaderPath, GL_VERTEX_SHADER);
        std::unique_ptr<Shader> fragmentShader = CreateShaderFromFile(config.m_fragmentShaderPath, GL_FRAGMENT_SHADER);

        GLuint const shader = glCreateProgram();
        glAttachShader(shader, vertexShader->GetID());
        glAttachShader(shader, fragmentShader->GetID());

        for (unsigned int i = 0; i < config.m_locations.size(); ++i)
        {
            glBindAttribLocation(shader, i, config.m_locations[i].c_str());
        }

        glLinkProgram(shader);

        return CreateMaterialMapEntry(config.m_name, Material(config.m_name, config.m_locations, shader));
    }
}
