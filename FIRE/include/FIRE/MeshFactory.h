#ifndef FIRE_MeshFactory_h
#define FIRE_MeshFactory_h

#include <memory>

namespace FIRE
{
class Mesh;
class MeshFactory
{
public:
    std::shared_ptr<Mesh> CreateCube();
    std::shared_ptr<Mesh> CreatePlane();
};

} // namespace FIRE

#endif // FIRE_MeshFactory_h
