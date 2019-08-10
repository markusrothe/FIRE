#ifndef FIRE_MeshFactory_h
#define FIRE_MeshFactory_h

#include <FIRE/Mesh3D.h>
#include <FIRE/MeshType.h>

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>

namespace FIRE
{

namespace MeshFactory
{
std::unique_ptr<Mesh3D> CreateCube(std::string name);
std::unique_ptr<Mesh3D> CreatePlane(std::string name);
std::unique_ptr<Mesh3D> CreateSphere(std::string name, uint32_t segments);
std::unique_ptr<Mesh3D> CreateLineGrid(std::string name, uint32_t width, uint32_t height);
std::unique_ptr<Mesh3D> CreateTriangleGrid(std::string name, uint32_t width, uint32_t height);
std::unique_ptr<Mesh3D> DoCreate(
    MeshCategory meshType,
    MeshPrimitives primitives,
    std::string const& name,
    std::vector<glm::vec3>&& positions,
    std::vector<glm::vec3>&& normals,
    std::vector<glm::vec2>&& uvs,
    std::vector<unsigned int>&& indices);

} // namespace MeshFactory
} // namespace FIRE

#endif // FIRE_MeshFactory_h
