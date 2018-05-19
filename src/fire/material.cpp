#include "material.h"

namespace Fire
{
    Material::Material(std::string const& name)
        : m_name(name.empty() ? "simple" : name)
        , m_bound(false)
    {
    }

    std::string Material::GetName() const
    {
        return m_name;
    }

    void Material::Bind()
    {
        m_bound = true;
    }

    void Material::Unbind()
    {
        m_bound = false;
    }

    bool Material::IsBound() const
    {
        return m_bound;
    }

} // namespace Fire
