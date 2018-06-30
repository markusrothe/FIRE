#include "material.h"

namespace Fire
{
    Material::Material(std::string const& name, std::unique_ptr<Shader>&& shader)
        : m_name(name.empty() ? "simple" : name)
	, m_shader(std::move(shader))
        , m_bound(false)
    {
    }

    Material::~Material()
    {

    }

    std::string Material::GetName() const
    {
        return m_name;
    }

    void Material::Bind()
    {
	m_shader->Bind();
    }

    void Material::Unbind()
    {
	m_shader->Unbind();
    }

    bool Material::IsBound() const
    {
        return m_shader->Bound();
    }

} // namespace Fire
