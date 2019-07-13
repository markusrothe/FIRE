#ifndef FIRE_MeshFactory_h
#define FIRE_MeshFactory_h

#include <FIRE/Mesh3D.h>
#include <FIRE/MeshHandle.h>
#include <FIRE/MeshType.h>
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>

namespace FIRE
{

class MeshManager
{
public:
    MeshHandle Create(
        MeshCategory meshType,
        MeshPrimitives primitives,
        std::string name,
        std::vector<glm::vec3>&& positions,
        std::vector<glm::vec3>&& normals,
        std::vector<unsigned int>&& indices);

    /* Triangle meshes */
    MeshHandle CreateCube(std::string name);
    MeshHandle CreatePlane(std::string name);
    MeshHandle CreateSphere(std::string name, uint32_t segments);
    MeshHandle CreateLineGrid(std::string name, uint32_t numLinesX, uint32_t numLinesY);

    Mesh3D* Lookup3D(MeshHandle const& handle);

private:
    MeshHandle DoCreate(
        MeshCategory meshType,
        MeshPrimitives primitives,
        std::string name,
        std::vector<glm::vec3>&& positions,
        std::vector<glm::vec3>&& normals,
        std::vector<unsigned int>&& indices);

    std::unordered_map<std::string, std::pair<MeshType, std::unique_ptr<Mesh3D>>> m_cache;
};

} // namespace FIRE

#endif // FIRE_MeshFactory_h
