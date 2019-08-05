#ifndef FIRE_Material_h
#define FIRE_Material_h
#include <FIRE/ShaderType.h>
#include <any>
#include <map>
#include <optional>
#include <string>
#include <unordered_map>

namespace FIRE
{
class Texture2D;
class Material
{
public:
    Material() = default;
    Material(std::string name, unsigned int shaderId);

    [[nodiscard]] std::string Name() const;
    [[nodiscard]] unsigned int ShaderId() const;
    void SetShaderParameter(std::string const& paramName, ShaderParameterType paramType, std::any paramValue);
    [[nodiscard]] std::optional<std::pair<ShaderParameterType, std::any>> GetShaderParameter(std::string const& paramName) const;
    [[nodiscard]] std::map<std::string, std::pair<ShaderParameterType, std::any>> GetShaderParameters() const;

    void AddTexture(Texture2D* tex, uint32_t slot);
    [[nodiscard]] Texture2D* GetTexture(uint32_t slot);
    [[nodiscard]] std::unordered_map<uint32_t, Texture2D*> GetTextures();

    bool operator==(Material const& other) const;
    bool operator!=(Material const& other) const;

private:
    std::string m_name{""};
    unsigned int m_shaderId{0};
    std::unordered_map<uint32_t, Texture2D*> m_textures;
    std::map<std::string, std::pair<ShaderParameterType, std::any>> m_shaderParams;
};
} // namespace FIRE

#endif