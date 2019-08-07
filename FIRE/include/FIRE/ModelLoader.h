#ifndef FIRE_MODELLOADER_H
#define FIRE_MODELLOADER_H

#include "Renderable.h"
#include <string>
namespace FIRE
{
class MeshManager;
class Material;
class TextureManager;
class ModelLoader
{
public:
    explicit ModelLoader(MeshManager& meshManager, TextureManager& texManager);

    std::vector<Renderable> Load(std::string const& fileContent, FIRE::Material const& material);
    std::vector<Renderable> LoadFromFile(std::string const& filepath, FIRE::Material const& material);

private:
    MeshManager& m_meshManager;
    TextureManager& m_texManager;
};
} // namespace FIRE

#endif //FIRE_MODELLOADER_H
