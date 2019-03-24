#include "MaterialManager.h"
#include "ShaderFactory.h"

namespace FIRE
{
MaterialManager::MaterialManager(std::unique_ptr<ShaderFactory> shaderFactory)
    : m_shaderFactory(std::move(shaderFactory))
{
    m_shaders.insert(std::make_pair("Default", m_shaderFactory->CreateDefaultShader()));
}

MaterialManager::~MaterialManager() = default;

unsigned int MaterialManager::GetShader(std::string const& materialName) const
{
    auto const shader = m_shaders.find(materialName);
    return (shader != m_shaders.end()) ? shader->second : 0u;
}
} // namespace FIRE
