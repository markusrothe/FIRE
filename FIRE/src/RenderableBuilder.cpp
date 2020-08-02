#include <FIRE/AssetFacade.h>
#include <FIRE/RenderableBuilder.h>
#include <cassert>
#include <sstream>

namespace FIRE
{
RenderableBuilder::RenderableBuilder(AssetFacade& assets, std::string const& prefix, uint32_t count)
    : assets(assets)
{
    renderables.reserve(count);
    auto const defaultMaterial = assets.GetMaterial("Default");
    for(auto i = 0u; i < count; ++i)
    {
        std::stringstream ss;
        ss << i;
        renderables.emplace_back(prefix + ss.str(), defaultMaterial, nullptr);
    }
}

std::vector<Renderable> RenderableBuilder::Build()
{
    return renderables;
}

RenderableBuilder& RenderableBuilder::WithMesh(std::string const& name)
{
    renderables[meshIdx++].mesh = assets.GetMesh(name);
    return *this;
}

RenderableBuilder& RenderableBuilder::WithTexture(std::string const& name, uint32_t slot)
{
    return WithTextures({{name, slot}});
}

RenderableBuilder& RenderableBuilder::WithMaterial(std::string const& name)
{
    if(materialIdx >= renderables.size())
    {
        throw std::runtime_error("Could not add material. Too few renderables.");
    }
    renderables[materialIdx++].material = assets.GetMaterial(name);
    return *this;
}

RenderableBuilder& RenderableBuilder::WithTextures(std::vector<std::pair<std::string, uint32_t>> const& textureNamesAndSlots)
{
    for(auto const& textureNameAndSlot : textureNamesAndSlots)
    {
        renderables[texIdx].material.AddTexture(assets.GetTexture(textureNameAndSlot.first), textureNameAndSlot.second);
    }
    texIdx++;
    return *this;
}
} // namespace FIRE
