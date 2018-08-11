#include "material.h"

namespace Fire
{
Material::Material(std::string const& name, GLuint shaderProgram)
    : m_name(name)
    , m_shaderProgram(shaderProgram)
    , m_bound(false)
{
}

Material::~Material() = default;

std::string Material::GetName() const { return m_name; }

void Material::Bind()
{
    glUseProgram(m_shaderProgram);
    m_bound = true;
}

void Material::Unbind()
{
    glUseProgram(0);
    m_bound = false;
}

bool Material::IsBound() const { return m_bound; }

} // namespace Fire
