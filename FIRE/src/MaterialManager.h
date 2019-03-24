#ifndef FIRE_MaterialManager_h
#define FIRE_MaterialManager_h

#include <memory>
#include <string>
#include <unordered_map>
namespace FIRE
{
class ShaderFactory;
class MaterialManager
{
public:
    explicit MaterialManager(std::unique_ptr<ShaderFactory> shaderFactory);
    ~MaterialManager();
    unsigned int GetShader(std::string const& materialName) const;

private:
    std::unique_ptr<ShaderFactory> m_shaderFactory;
    std::unordered_map<std::string, unsigned int> m_shaders;
};
} // namespace FIRE

#endif // !FIRE_MaterialManager_h
