#ifndef FIRE_MaterialFactory_h
#define FIRE_MaterialFactory_h

#include <FIRE/Material.h>
#include <FIRE/ShaderType.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace FIRE
{

class ShaderFactory;
class MaterialFactory
{
public:
    explicit MaterialFactory(std::unique_ptr<ShaderFactory> shaderFactory);

    ~MaterialFactory();

    Material CreateDefaultMaterial();

    Material CreateMaterial(std::string const& name, std::vector<std::pair<ShaderType, std::string>> const& shaders);

private:
    std::unique_ptr<ShaderFactory> m_shaderFactory;
};
} // namespace FIRE

#endif // !FIRE_MaterialFactory_h
