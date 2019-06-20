#include <FIRE/Material.h>
#include <FIRE/MaterialFactory.h>
#include <FIRE/ShaderFactory.h>

namespace FIRE
{
namespace MaterialFactory
{
Material Create(std::string const& name, std::vector<std::pair<ShaderType, std::string>> const& shaderCode, ShaderFactory& shaderFactory)
{
    return Material(name, shaderFactory.Create(shaderCode));
}

Material CreateDefault(ShaderFactory& shaderFactory)
{
    return Material("Default", shaderFactory.CreateDefaultShader());
}
} // namespace MaterialFactory
} // namespace FIRE
