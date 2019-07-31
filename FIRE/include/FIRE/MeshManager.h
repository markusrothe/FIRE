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
    Mesh3D* Create(
        MeshCategory meshType,
        MeshPrimitives primitives,
        std::string name,
        std::vector<glm::vec3>&& positions,
        std::vector<glm::vec3>&& normals,
        std::vector<glm::vec2>&& uvs,
        std::vector<unsigned int>&& indices);

    Mesh3D* CreateCube(std::string name);
    Mesh3D* CreatePlane(std::string name);
    Mesh3D* CreateSphere(std::string name, uint32_t segments);
    Mesh3D* CreateLineGrid(std::string name, uint32_t width, uint32_t height);
    Mesh3D* CreateTriangleGrid(std::string name, uint32_t width, uint32_t height);

    std::vector<Mesh3D*> CreateFromFile(std::string name, std::string filename);

private:
    Mesh3D* DoCreate(
        MeshCategory meshType,
        MeshPrimitives primitives,
        std::string name,
        std::vector<glm::vec3>&& positions,
        std::vector<glm::vec3>&& normals,
        std::vector<glm::vec2>&& uvs,
        std::vector<unsigned int>&& indices);

    std::unordered_map<std::string, std::unique_ptr<Mesh3D>>::const_iterator Lookup(std::string const& name) const;

    std::unordered_map<std::string, std::unique_ptr<Mesh3D>> m_cache;
};

} // namespace FIRE

#endif // FIRE_MeshFactory_h
