#ifndef FIRE_Material_h
#define FIRE_Material_h
#include <FIRE/ShaderType.h>
#include <any>
#include <map>
#include <optional>
#include <string>

namespace FIRE
{

class Material
{
public:
    Material() = default;
    Material(std::string name, unsigned int shaderId);

    std::string Name() const;
    unsigned int ShaderId() const;
    void SetShaderParameter(std::string const& paramName, ShaderParameterType paramType, std::any paramValue);
    std::optional<std::pair<ShaderParameterType, std::any>> GetShaderParameter(std::string const& paramName) const;
    std::map<std::string, std::pair<ShaderParameterType, std::any>> GetShaderParameters() const;

private:
    std::string m_name{""};
    unsigned int m_shaderId{0};
    std::map<std::string, std::pair<ShaderParameterType, std::any>> m_shaderParams;
};
} // namespace FIRE

#endif