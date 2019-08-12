#ifndef FIRE_MODELLOADER_H
#define FIRE_MODELLOADER_H

#include <FIRE/Mesh3D.h>
#include <FIRE/Texture2D.h>
#include <memory>
#include <string>

struct aiMesh;
namespace FIRE
{

struct Model
{
    std::unique_ptr<Mesh3D> mesh;
    std::string texturePath;
    Texture2D::WrappingMode textureWrapping;
};

class ModelLoader
{
public:
    enum class Source
    {
        Memory,
        File
    };

    explicit ModelLoader(Source source, std::string const& str);
    [[nodiscard]] Model const& GetModel(uint32_t meshIndex) const;
    Model StealModel(uint32_t meshIndex);

    [[nodiscard]] std::pair<std::string, Texture2D::WrappingMode> GetTexture(uint32_t meshIndex) const;
    [[nodiscard]] uint32_t GetNumModels() const;

private:
    void CheckMeshIndex(uint32_t meshIndex) const;
    std::vector<Model> m_models;
};
} // namespace FIRE

#endif //FIRE_MODELLOADER_H
