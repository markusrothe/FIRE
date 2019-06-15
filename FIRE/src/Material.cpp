#include <FIRE/Material.h>
#include <FIRE/Matrix.h>

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

void Material::SetShaderParameter(std::string const& paramName, FIRE::ShaderParameterType paramType, FIRE::Matrix4x4&& paramValue)
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

} // namespace FIRE