#include <FIRE/Mesh.h>
#include <FIRE/MeshManager.h>
#include <algorithm>
#include <cmath>
#include <iostream>
namespace FIRE
{
Mesh* MeshManager::Lookup(MeshHandle const& handle)
{
    auto mesh = m_cache.find(handle.name);
    if(mesh != std::cend(m_cache))
    {
        if(handle.type != mesh->second.first)
        {
            throw std::runtime_error(
                "A mesh of a different type with that name already exists.");
        }

        return mesh->second.second.get();
    }

    return nullptr;
}

MeshHandle MeshManager::CreateCube(std::string name)
{
    if(Lookup({name, MeshType::Cube}))
    {
        return {name, MeshType::Cube};
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

MeshHandle MeshManager::CreatePlane(std::string name)
{

    if(Lookup({name, MeshType::Plane}))
    {
        return {name, MeshType::Plane};
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

MeshHandle MeshManager::CreateSphere(std::string name, uint32_t segments)
{
    if(Lookup({name, MeshType::Sphere}))
    {
        return {name, MeshType::Sphere};
    }

    std::vector<FIRE::Vector3> positions;
    std::vector<FIRE::Vector3> normals;
    std::vector<unsigned int> indices;

    // top
    positions.emplace_back(0.0f, 1.0f, 0.0f);
    normals.emplace_back(0.0f, 1.0f, 0.0f);

    // middle
    for(auto j = 0u; j < segments - 1; ++j)
    {
        double polarAngle = M_PI * double(j + 1) / double(segments); // 0° - 180° divided into segments
        double const sinPolar = std::sin(polarAngle);
        double const cosPolar = std::cos(polarAngle);

        for(auto i = 0u; i < segments; ++i)
        {
            double const azimuth = 2.0 * M_PI * double(i) / double(segments); // 0° - 360° divided into segments
            double const sinAzimuth = std::sin(azimuth);
            double const cosAzimuth = std::cos(azimuth);
            double const x = sinPolar * cosAzimuth;
            double const y = cosPolar;
            double const z = sinPolar * sinAzimuth;
            Vector3 pos(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
            positions.push_back(pos);
            normals.push_back(pos);
        }
    }

    //bottom
    positions.emplace_back(0.0f, -1.0f, 0.0f);
    normals.emplace_back(0.0f, -1.0f, 0.0f);

    for(uint32_t i = 0; i < segments; ++i)
    {
        uint32_t const a = i + 1;
        uint32_t const b = (i + 1) % segments + 1;
        indices.push_back(0); // top
        indices.push_back(b); // azimuth is increased clock-wise, so b comes before a
        indices.push_back(a);
    }

    for(uint32_t j = 0; j < segments - 2; ++j)
    {
        uint32_t aStart = j * segments + 1;
        uint32_t bStart = (j + 1) * segments + 1;
        for(uint32_t i = 0; i < segments; ++i)
        {
            const uint32_t a = aStart + i;
            const uint32_t a1 = aStart + (i + 1) % segments;
            const uint32_t b = bStart + i;
            const uint32_t b1 = bStart + (i + 1) % segments;
            indices.push_back(a);
            indices.push_back(a1);
            indices.push_back(b1);

            indices.push_back(a);
            indices.push_back(b1);
            indices.push_back(b);
        }
    }

    for(uint32_t i = 0; i < segments; ++i)
    {
        uint32_t const a = i + segments * (segments - 2) + 1;
        uint32_t const b = (i + 1) % segments + segments * (segments - 2) + 1;
        indices.push_back(static_cast<unsigned int>(positions.size() - 1)); // bottom
        indices.push_back(a);
        indices.push_back(b);
    }

    return Create(
        MeshType::Sphere,
        std::move(name),
        std::move(positions),
        std::move(normals),
        std::move(indices));
}

MeshHandle MeshManager::Create(
    MeshType meshType,
    std::string name,
    std::vector<FIRE::Vector3>&& positions,
    std::vector<FIRE::Vector3>&& normals,
    std::vector<unsigned int>&& indices)
{
    auto mesh = std::make_unique<Mesh>(name);
    mesh->AddPositions(positions);
    mesh->AddNormals(normals);
    mesh->AddIndices(indices);

    mesh->GetVertexDeclaration().AddSection("vPos", 3u, 0u);
    mesh->GetVertexDeclaration().AddSection("vNormal", 3u, positions.size() * sizeof(float) * 3);

    m_cache.insert(std::make_pair(name, std::make_pair(meshType, std::move(mesh))));
    return {name, meshType};
}

} // namespace FIRE
