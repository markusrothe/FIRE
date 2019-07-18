#ifndef FIRE_MaterialFactory_h
#define FIRE_MaterialFactory_h

#include <FIRE/Material.h>
#include <FIRE/ShaderFactory.h>
#include <FIRE/ShaderType.h>

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace FIRE
{

class MaterialFactory
{
public:
    explicit MaterialFactory(std::unique_ptr<ShaderFactory> shaderFactory);

    ~MaterialFactory();

    Material CreateDefaultMaterial();
    Material CreateMaterial(std::string const& name, std::vector<std::pair<ShaderType, std::string>> const& shaderCode);
    Material CreateMaterialFromFiles(std::string const& name, std::vector<std::pair<ShaderType, std::string>> const& shaders);

    Material GetMaterial(std::string const& name) const;

private:
    std::unique_ptr<ShaderFactory> m_shaderFactory;
    std::map<std::string, uint32_t> m_cachedShaders;
};
} // namespace FIRE

#endif // !FIRE_MaterialFactory_h
