#ifndef FIRE_MODELLOADER_H
#define FIRE_MODELLOADER_H

#include <FIRE/Mesh3D.h>
#include <FIRE/Texture2D.h>
#include <memory>
#include <string>

class aiMesh;
namespace FIRE
{
class Material;
class TextureManager;
class ModelLoader
{
public:
    enum class Source
    {
        Memory,
        File
    };
    explicit ModelLoader(Source source, std::string const& str);

    [[nodiscard]] std::vector<glm::vec3> GetPositions(uint32_t meshIndex) const;
    [[nodiscard]] std::vector<glm::vec3> GetNormals(uint32_t meshIndex) const;
    [[nodiscard]] std::vector<glm::vec2> GetTextureCoordinates(uint32_t meshIndex) const;
    [[nodiscard]] std::vector<uint32_t> GetIndices(uint32_t meshIndex) const;
    [[nodiscard]] std::string GetTexture(uint32_t meshIndex) const;
    [[nodiscard]] uint32_t GetNumMeshes() const;

private:
    void CheckMeshIndex(uint32_t meshIndex) const;
    std::vector<std::unique_ptr<Mesh3D>> m_meshes;
    std::vector<std::pair<std::string, Texture2D::WrappingMode>> m_textures;
};
} // namespace FIRE

#endif //FIRE_MODELLOADER_H
