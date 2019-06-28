#ifndef FIRE_MeshFactory_h
#define FIRE_MeshFactory_h

#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>

namespace FIRE
{
class Mesh;
class MeshFactory
{
public:
    std::shared_ptr<Mesh> CreateCube(std::string name);
    std::shared_ptr<Mesh> CreatePlane(std::string name);
    std::shared_ptr<Mesh> CreateSphere(std::string name, size_t segments);

private:
    enum class MeshType
    {
        Plane,
        Cube,
        Sphere
    };

    std::weak_ptr<Mesh> Lookup(std::string const& name, MeshType meshType);

    std::shared_ptr<Mesh> Create(
        MeshType meshType,
        std::string&& name,
        std::vector<FIRE::Vector3>&& positions,
        std::vector<FIRE::Vector3>&& normals,
        std::vector<unsigned int>&& indices);

    std::unordered_map<std::string, std::pair<MeshType, std::weak_ptr<Mesh>>> m_cache;
};

} // namespace FIRE

#endif // FIRE_MeshFactory_h
