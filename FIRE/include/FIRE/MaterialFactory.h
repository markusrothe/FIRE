#ifndef FIRE_MaterialManager_h
#define FIRE_MaterialManager_h

#include <FIRE/Material.h>
#include <FIRE/ShaderType.h>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace FIRE
{
class ShaderFactory;
namespace MaterialFactory
{

Material Create(std::string const& name, std::vector<std::pair<ShaderType, std::string>> const& shaderCode, ShaderFactory& shaderFactory);
Material CreateDefault(ShaderFactory& shaderFactory);

} // namespace MaterialFactory
} // namespace FIRE

#endif // !FIRE_MaterialManager_h
