#include <FIRE/AssetFacade.h>
#include <FIRE/RenderableBuilder.h>
#include <cassert>
#include <sstream>

namespace FIRE
{
RenderableBuilder::RenderableBuilder(
    AssetFacade& assets, std::string const& prefix, uint32_t count)
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
    return WithMesh(assets.GetMesh(name));
}

RenderableBuilder& RenderableBuilder::WithMesh(std::string const& name, MeshCategory category)
{
    assets.CreateMesh(name, category);
    return WithMesh(name);
}

RenderableBuilder& RenderableBuilder::WithMesh(Mesh3D* mesh)
{
    if(meshIdx >= renderables.size())
    {
        throw std::runtime_error("Could not add mesh. Too few renderables.");
    }
    renderables[meshIdx++].mesh = mesh;
    return *this;
}

RenderableBuilder& RenderableBuilder::WithTexture(std::string const& name, uint32_t slot)
{
    return WithTextures({{name, slot}});
}

RenderableBuilder& RenderableBuilder::WithTexture(Texture2D* texture, uint32_t slot)
{
    renderables[texIdx++].material.AddTexture(texture, slot);
    return *this;
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
RenderableBuilder& RenderableBuilder::WithNewTexture(
    std::string const& name,
    std::string const& filepath,
    Texture2D::WrappingMode wrapping,
    uint32_t slot)
{
    assets.SubmitTexture(name, filepath, wrapping);
    return WithTexture(name, slot);
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
