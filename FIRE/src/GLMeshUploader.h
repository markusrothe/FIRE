#ifndef FIRE_GLMESHUPLOADER_H
#define FIRE_GLMESHUPLOADER_H

#include "MeshUploader.h"
#include <cstdint>
#include <string>
#include <unordered_map>
namespace FIRE
{
class GLMeshUploader : public MeshUploader
{
public:
    VertexLayout Upload(Mesh3D const& mesh, uint32_t shader) override;

private:
    std::unordered_map<std::string, VertexLayout> m_uploadedMeshes{};
};
} // namespace FIRE

#endif //FIRE_GLMESHUPLOADER_H
