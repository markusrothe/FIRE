#ifndef FIRE_RENDERABLEBUILDER_H
#define FIRE_RENDERABLEBUILDER_H

#include <FIRE/Renderable.h>
#include <vector>
namespace FIRE
{
class AssetFacade;
class RenderableBuilder
{
public:
    RenderableBuilder(AssetFacade& assets, std::string const& prefix, uint32_t count);
    std::vector<Renderable> Build();

    RenderableBuilder& WithMesh(std::string const& name);
    RenderableBuilder& WithMesh(std::string const& name, MeshCategory category);
    RenderableBuilder& WithMesh(Mesh3D* mesh);
    RenderableBuilder& WithTexture(std::string const& name, uint32_t slot);
    RenderableBuilder& WithTexture(Texture2D* texture, uint32_t slot);
    RenderableBuilder& WithNewTexture(std::string const& name, std::string const& filepath, Texture2D::WrappingMode wrapping, uint32_t slot);
    RenderableBuilder& WithTextures(std::vector<std::pair<std::string, uint32_t>> const& textureNamesAndSlots);
    RenderableBuilder& WithMaterial(std::string const& name);

private:
    AssetFacade& assets;
    std::vector<Renderable> renderables;
    uint32_t meshIdx{0u};
    uint32_t materialIdx{0u};
    uint32_t texIdx{0u};
};
} // namespace FIRE

#endif //FIRE_RENDERABLEBUILDER_H
