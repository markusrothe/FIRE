#include <FIRE/Material.h>

namespace FIRE
{
Material::Material(std::string name, unsigned int shaderId)
    : m_name(std::move(name))
    , m_shaderId(shaderId)
{
}

std::string Material::Name() const
{
    return m_name;
}

unsigned int Material::ShaderId() const
{
    return m_shaderId;
}
} // namespace FIRE