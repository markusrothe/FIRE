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

void Material::SetShaderParameter(std::string const& paramName, FIRE::ShaderParameterType paramType, std::any paramValue)
{
    m_shaderParams[paramName] = std::make_pair(paramType, std::move(paramValue));
}

std::optional<std::pair<ShaderParameterType, std::any>> Material::GetShaderParameter(std::string const& paramName) const
{
    auto shaderParam = m_shaderParams.find(paramName);
    if(shaderParam != m_shaderParams.end())
    {
        return shaderParam->second;
    }

    return std::optional<std::pair<ShaderParameterType, std::any>>();
}

std::map<std::string, std::pair<ShaderParameterType, std::any>> Material::GetShaderParameters() const
{
    return m_shaderParams;
}

bool Material::operator==(Material const& other) const
{
    return m_name == other.m_name;
}

bool Material::operator!=(Material const& other) const
{
    return !(*this == other);
}
void Material::AddTexture(Texture2D* tex, uint32_t slot)
{
    m_textures[slot] = tex;
}

Texture2D* Material::GetTexture(uint32_t slot)
{
    if(auto it = m_textures.find(slot); it != m_textures.end())
    {
        return it->second;
    }

    return nullptr;
}
std::unordered_map<uint32_t, Texture2D*> Material::GetTextures()
{
    return m_textures;
}

} // namespace FIRE