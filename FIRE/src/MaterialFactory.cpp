#include <FIRE/Material.h>
#include <FIRE/MaterialFactory.h>
#include <algorithm>
#include <fstream>
#include <stdexcept>

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
MaterialFactory::MaterialFactory(
    std::unique_ptr<ShaderFactory> shaderFactory)
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
    auto const shader = m_cachedShaders.find(name);
    if(shader != m_cachedShaders.end())
    {
        return Material(name, shader->second);
    }

    auto const shaderID = m_shaderFactory->Create(shaderCode);
    m_cachedShaders.insert(std::make_pair(name, shaderID));
    return Material(name, shaderID);
}

Material MaterialFactory::CreateMaterialFromFiles(std::string const& name, std::string vertexShaderFile, std::string fragmentShaderFile)
{
    Shaders const shaderCode = {
        {ShaderType::VERTEX_SHADER, GetFileContent(vertexShaderFile)},
        {ShaderType::FRAGMENT_SHADER, GetFileContent(fragmentShaderFile)}};

    return CreateMaterial(name, shaderCode);
}

Material MaterialFactory::GetMaterial(std::string const& name) const
{
    auto const shader = m_cachedShaders.find(name);
    if(shader != m_cachedShaders.end())
    {
        return Material(name, shader->second);
    }

    throw std::logic_error("No element with name " + name + "found.");
}

} // namespace FIRE
