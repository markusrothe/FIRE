#include <FIRE/Material.h>
#include <FIRE/MaterialFactory.h>

namespace FIRE
{

MaterialFactory::MaterialFactory(std::unique_ptr<ShaderFactory> shaderFactory)
    : m_shaderFactory(std::move(shaderFactory))
{
}

MaterialFactory::~MaterialFactory() = default;

Material MaterialFactory::CreateDefaultMaterial()
{
    return Material("Default", m_shaderFactory->CreateDefaultShader());
}

Material MaterialFactory::CreateMaterial(std::string const& name, std::vector<std::pair<ShaderType, std::string>> const& shaderCode)
{
    return Material(name, m_shaderFactory->Create(shaderCode));
}

} // namespace FIRE
