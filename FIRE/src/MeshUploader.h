#ifndef FIRE_MESHUPLOADER_H
#define FIRE_MESHUPLOADER_H

#include <cstdint>
namespace FIRE
{
class VertexLayout;
class Mesh3D;
class MeshUploader
{
public:
    virtual ~MeshUploader() = default;
    virtual VertexLayout Upload(Mesh3D const& mesh, uint32_t shader) = 0;
};
} // namespace FIRE
#endif //FIRE_MESHUPLOADER_H
