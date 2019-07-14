#include <FIRE/Material.h>
#include <FIRE/MaterialFactory.h>
#include <algorithm>
#include <fstream>
#include <iterator>

namespace FIRE
{
namespace
{
std::string GetFileContent(std::string const& filePath)
{
    std::ifstream file(filePath);
    std::string const content{(std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()};
    return content;
}
} // namespace
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

Material MaterialFactory::CreateMaterialFromFiles(std::string const& name, std::vector<std::pair<ShaderType, std::string>> const& shaders)
{
    FIRE::Shaders shaderCode;
    std::transform(
        shaders.begin(),
        shaders.end(),
        std::back_inserter(shaderCode),
        [](auto const& shaderDescriptor) {
            return std::make_pair(shaderDescriptor.first, GetFileContent(shaderDescriptor.second));
        });

    return Material(name, m_shaderFactory->Create(shaderCode));
}
} // namespace FIRE
