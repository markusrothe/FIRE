#ifndef FIRE_ASSETFACADE_H
#define FIRE_ASSETFACADE_H

#include <FIRE/FontCharacter.h>
#include <FIRE/Material.h>
#include <FIRE/Mesh3D.h>
#include <FIRE/OverlayBuilder.h>
#include <FIRE/Renderable.h>
#include <FIRE/RenderableBuilder.h>
#include <FIRE/ShaderType.h>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace FIRE
{
class TextureFactory;
class ShaderFactory;
class ModelLoader;
class AssetFacade
{
public:
    AssetFacade(std::unique_ptr<TextureFactory> texFactory, std::unique_ptr<ShaderFactory> shaderFactory);
    ~AssetFacade();

    void SubmitTexture(std::string const& name, std::string const& textureFilePath, Texture2D::WrappingMode wrappingMode);
    void SubmitTexture(std::string const& name, std::unique_ptr<Texture2D> texture);
    void SubmitTexture(std::string const& name, uint32_t width, uint32_t height, std::vector<uint8_t> const& data, uint8_t numComponents, Texture2D::WrappingMode wrappingMode, Texture2D::Filter filter);
    Texture2D* GetTexture(std::string const& name) const;

    FontCharacter CreateFontCharacter(char c);

    void SubmitShaders(std::string const& name, Shaders const& shaders);
    void SubmitShadersFromFiles(std::string const& name, Shaders const& shaders);
    [[nodiscard]] Material GetMaterial(std::string const& name) const;

    void SubmitMesh(std::string const& name, std::unique_ptr<Mesh3D> mesh);
    [[nodiscard]] Mesh3D* GetMesh(std::string const&) const;
    void CreateMesh(std::string const& name, MeshCategory meshCategory);

    void SubmitModel(std::string const& name, std::string const& fileContent);
    void SubmitModelFromFile(std::string const& name, std::string const& filePath);
    [[nodiscard]] std::vector<Mesh3D*> GetModelMeshes(std::string const& name) const;

    RenderableBuilder CreateRenderables(std::string const& namePrefix, uint32_t count);
    std::vector<Renderable> CreateModelRenderables(std::string const& namePrefix, std::string const& modelName, std::string const& overrideMaterial);

    OverlayBuilder CreateTextOverlays(std::string const& namePrefix, uint32_t count);

    struct Foo
    {
        std::string name;
        std::vector<std::string> meshes;
        std::vector<std::string> textures;
    };

private:
    void ProcessModel(std::string const& name, ModelLoader& loader);

    std::unique_ptr<TextureFactory> m_texFactory;
    std::unique_ptr<ShaderFactory> m_shaderFactory;

    std::unordered_map<std::string, std::unique_ptr<Texture2D>> m_textures;
    std::unordered_map<char, FontCharacter> m_fontCharacters;
    std::unordered_map<std::string, Material> m_materials;
    std::unordered_map<std::string, std::unique_ptr<Mesh3D>> m_meshes;

    std::unordered_map<std::string, Foo> m_models;
};
} // namespace FIRE

#endif // FIRE_ASSETFACADE_H
