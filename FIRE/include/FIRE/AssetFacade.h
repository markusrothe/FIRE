#ifndef FIRE_ASSETFACADE_H
#define FIRE_ASSETFACADE_H

#include <FIRE/FontCharacter.h>
#include <FIRE/Material.h>
#include <FIRE/Mesh3D.h>
#include <FIRE/ShaderType.h>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace FIRE
{
class TextureFactory;
class ShaderFactory;
class AssetFacade
{
public:
    explicit AssetFacade(
        std::unique_ptr<TextureFactory> texFactory,
        std::unique_ptr<ShaderFactory> shaderFactory);
    ~AssetFacade();

    void SubmitTexture(std::string const& name, std::string const& textureFilePath, Texture2D::WrappingMode wrappingMode);
    void SubmitTexture(std::string const& name, std::unique_ptr<Texture2D> texture);
    void CreateTexture(
        std::string const& name,
        uint32_t width,
        uint32_t height,
        std::vector<uint8_t> const& data,
        uint8_t numComponents,
        Texture2D::WrappingMode wrappingMode,
        Texture2D::Filter filter);
    [[nodiscard]] Texture2D* GetTexture(std::string const& name) const;
    FontCharacter CreateFontCharacter(char c);

    void SubmitShaders(std::string const& name, Shaders shaders);
    void SubmitShadersFromFiles(std::string const& name, Shaders shaders);
    [[nodiscard]] Material GetMaterial(std::string const& name) const;

    void SubmitMesh(std::string const& name, std::unique_ptr<Mesh3D> mesh);
    [[nodiscard]] Mesh3D* GetMesh(std::string const&) const;
    void CreateMesh(std::string const& name, MeshCategory meshCategory);

    void SubmitModel(std::string const& name, std::string const& fileContent);
    [[nodiscard]] std::vector<Mesh3D*> GetModelMeshes(std::string const& name) const;

private:
    std::unique_ptr<TextureFactory> m_texFactory;
    std::unique_ptr<ShaderFactory> m_shaderFactory;

    std::unordered_map<std::string, std::unique_ptr<Texture2D>> m_textures;
    std::unordered_map<char, FontCharacter> m_fontCharacters;
    std::unordered_map<std::string, Material> m_materials;
    std::unordered_map<std::string, std::unique_ptr<Mesh3D>> m_meshes;
    std::unordered_map<std::string, std::pair<std::vector<Mesh3D*>, std::vector<Texture2D*>>> m_modelAssets;
};
} // namespace FIRE

#endif // FIRE_ASSETFACADE_H
