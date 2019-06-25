#include <FIRE/Mesh.h>
#include <FIRE/MeshFactory.h>
#include <algorithm>
namespace FIRE
{

std::weak_ptr<Mesh> MeshFactory::Lookup(std::string const& key, MeshType meshType)
{
    auto mesh = m_cache.find(key);
    if(mesh != std::cend(m_cache))
    {
        if(meshType != mesh->second.first)
        {
            throw std::runtime_error(
                "A mesh of a different type with that name already exists.");
        }

        return mesh->second.second;
    }

    return std::weak_ptr<Mesh>();
}

std::shared_ptr<Mesh> MeshFactory::CreateCube(std::string name)
{
    if(auto ptr = Lookup(name, MeshType::Cube).lock())
    {
        return ptr;
    }

    std::vector<FIRE::Vector3> positions = {{-1.0f, -1.0f, -1.0f},
                                            {-1.0f, -1.0f, -1.0f},
                                            {-1.0f, -1.0f, -1.0f},

                                            {1.0f, -1.0f, 1.0f},
                                            {1.0f, -1.0f, 1.0f},
                                            {1.0f, -1.0f, 1.0f},

                                            {1.0f, -1.0f, -1.0f},
                                            {1.0f, -1.0f, -1.0f},
                                            {1.0f, -1.0f, -1.0f},

                                            {-1.0f, -1.0f, 1.0f},
                                            {-1.0f, -1.0f, 1.0f},
                                            {-1.0f, -1.0f, 1.0f},

                                            {-1.0f, 1.0f, 1.0f},
                                            {-1.0f, 1.0f, 1.0f},
                                            {-1.0f, 1.0f, 1.0f},

                                            {1.0f, 1.0f, 1.0f},
                                            {1.0f, 1.0f, 1.0f},
                                            {1.0f, 1.0f, 1.0f},

                                            {1.0f, 1.0f, -1.0f},
                                            {1.0f, 1.0f, -1.0f},
                                            {1.0f, 1.0f, -1.0f},

                                            {-1.0f, 1.0f, -1.0f},
                                            {-1.0f, 1.0f, -1.0f},
                                            {-1.0f, 1.0f, -1.0f}};

    std::vector<FIRE::Vector3> normals = {{0.0f, -1.0f, 0.0f},
                                          {0.0f, 0.0f, -1.0f},
                                          {-1.0f, 0.0f, 0.0f},

                                          {0.0f, 0.0f, 1.0f},
                                          {1.0f, 0.0f, 0.0f},
                                          {0.0f, -1.0f, 0.0f},

                                          {0.0f, -1.0f, 0.0f},
                                          {1.0f, 0.0f, 0.0f},
                                          {0.0f, 0.0f, -1.0f},

                                          {0.0f, -1.0f, 0.0f},
                                          {-1.0f, 0.0f, 0.0f},
                                          {0.0f, 0.0f, 1.0f},

                                          {-1.0f, 0.0f, 0.0f},
                                          {0.0f, 0.0f, 1.0f},
                                          {0.0f, 1.0f, 0.0f},

                                          {1.0f, 0.0f, 0.0f},
                                          {0.0f, 1.0f, 0.0f},
                                          {0.0f, 0.0f, 1.0f},

                                          {1.0f, 0.0f, 0.0f},
                                          {0.0f, 1.0f, 0.0f},
                                          {0.0f, 0.0f, -1.0f},

                                          {-1.0f, 0.0f, 0.0f},
                                          {0.0f, 1.0f, 0.0f},
                                          {0.0f, 0.0f, -1.0f}};

    std::vector<unsigned int> indices = {
        11, 3, 17, 11, 17, 13,  // front
        4, 7, 18, 4, 18, 15,    // right
        8, 1, 23, 8, 23, 20,    // back
        2, 10, 12, 2, 12, 21,   // left
        14, 16, 19, 14, 19, 22, // top
        0, 6, 5, 0, 5, 9        // down
    };
    return Create(
        MeshType::Cube,
        std::move(name),
        std::move(positions),
        std::move(normals),
        std::move(indices));
}

std::shared_ptr<Mesh> MeshFactory::CreatePlane(std::string name)
{
    if(auto ptr = Lookup(name, MeshType::Plane).lock())
    {
        return ptr;
    }

    std::vector<FIRE::Vector3> positions = {{-1.0f, 0.0f, -1.0f},
                                            {-1.0f, 0.0f, 1.0f},
                                            {1.0f, 0.0f, 1.0f},
                                            {1.0f, 0.0f, -1.0f}};

    std::vector<FIRE::Vector3> normals;
    normals.reserve(4u);
    for(auto i = 0u; i < 4u; ++i)
    {
        normals.emplace_back(0.0f, 1.0f, 0.0f);
    }

    std::vector<unsigned int> indices = {0, 1, 2, 0, 2, 3};

    return Create(
        MeshType::Plane,
        std::move(name),
        std::move(positions),
        std::move(normals),
        std::move(indices));
}

std::shared_ptr<Mesh> MeshFactory::Create(
    MeshType meshType,
    std::string&& name,
    std::vector<FIRE::Vector3>&& positions,
    std::vector<FIRE::Vector3>&& normals,
    std::vector<unsigned int>&& indices)
{
    auto mesh = std::make_shared<Mesh>(std::move(name));
    mesh->AddPositions(positions);
    mesh->AddNormals(normals);
    mesh->AddIndices(indices);
    m_cache.insert(std::make_pair(mesh->Name(), std::make_pair(meshType, mesh)));
    return mesh;
}

} // namespace FIRE
