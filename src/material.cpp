#include "material.h"

#include <glm/gtc/type_ptr.hpp>

namespace blocks
{
    Material::Material(std::string const name
        , std::vector<std::string> const& locations
        , GLuint shaderProgram)
        : m_name(name)
        , m_locations(locations)
        , m_shaderID(shaderProgram)
    {

    }

    void Material::Bind() const
    {
        glUseProgram(m_shaderID);
    }

    void Material::Unbind() const
    {
        glUseProgram(0);
    }

    std::vector<std::string> const& Material::GetLocations() const
    {
        return m_locations;
    }

    GLuint Material::GetShaderID() const
    {
        return m_shaderID;
    }

    void Material::Uniform(glm::mat4x4 const& matrix, std::string const name) const
    {
        auto const uniformLocation = glGetUniformLocation(m_shaderID, name.c_str());
        glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void Material::Uniform(unsigned int i, std::string const name) const
    {
        auto const uniformLocation = glGetUniformLocation(m_shaderID, name.c_str());
        glUniform1ui(uniformLocation, i);
    }
}
