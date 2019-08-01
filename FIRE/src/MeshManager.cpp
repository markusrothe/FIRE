#include <FIRE/MeshManager.h>
#include <algorithm>
#include <assimp/Importer.hpp>
#include <assimp/cimport.h>
#include <assimp/matrix4x4.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <cmath>
#include <iostream>
#include <sstream>

namespace FIRE
{
namespace
{
void ValidateMeshCategory(MeshCategory lhs, MeshCategory rhs)
{
    if(lhs != rhs)
    {
        throw std::runtime_error("A different mesh with the same name exists already.");
    }
}
} // namespace

Mesh3D* MeshManager::Create(
    MeshCategory meshCategory,
    MeshPrimitives primitives,
    std::string name,
    std::vector<glm::vec3>&& positions,
    std::vector<glm::vec3>&& normals,
    std::vector<glm::vec2>&& uvs,
    std::vector<unsigned int>&& indices)
{
    if(auto it = Lookup(name); it != m_cache.end())
    {
        ValidateMeshCategory(it->second->GetMeshType().category, MeshCategory::Custom);
        return it->second.get();
    }

    return DoCreate(meshCategory, primitives, name, std::move(positions), std::move(normals), std::move(uvs), std::move(indices));
}

Mesh3D* MeshManager::CreateCube(std::string name)
{
    if(auto it = Lookup(name); it != m_cache.end())
    {
        ValidateMeshCategory(it->second->GetMeshType().category, MeshCategory::Cube);
        return it->second.get();
    }

    std::vector<glm::vec3> positions = {{-1.0f, -1.0f, -1.0f},
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

    std::vector<glm::vec3> normals = {{0.0f, -1.0f, 0.0f},
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
    std::vector<glm::vec2> uvs = {
        {0, 0},
        {1, 0},
        {0, 0},

        {1, 0},
        {0, 0},
        {1, 1},

        {1, 0},
        {1, 0},
        {0, 0},

        {0, 1},
        {1, 0},
        {0, 0},

        {1, 1},
        {0, 1},
        {0, 0},

        {0, 1},
        {1, 0},
        {1, 1},

        {1, 1},
        {1, 1},
        {0, 1},

        {0, 1},
        {0, 1},
        {1, 1}};

    std::vector<unsigned int> indices = {
        11, 3, 17, 11, 17, 13,  // front
        4, 7, 18, 4, 18, 15,    // right
        8, 1, 23, 8, 23, 20,    // back
        2, 10, 12, 2, 12, 21,   // left
        14, 16, 19, 14, 19, 22, // top
        0, 6, 5, 0, 5, 9        // down
    };

    return DoCreate(
        MeshCategory::Cube,
        MeshPrimitives::Triangles,
        std::move(name),
        std::move(positions),
        std::move(normals),
        std::move(uvs),
        std::move(indices));
}

Mesh3D* MeshManager::CreatePlane(std::string name)
{
    if(auto it = Lookup(name); it != m_cache.end())
    {
        ValidateMeshCategory(it->second->GetMeshType().category, MeshCategory::Plane);
        return it->second.get();
    }

    std::vector<glm::vec3> positions = {{-1.0f, 0.0f, -1.0f},
                                        {-1.0f, 0.0f, 1.0f},
                                        {1.0f, 0.0f, 1.0f},
                                        {1.0f, 0.0f, -1.0f}};

    std::vector<glm::vec3> normals;
    normals.reserve(4u);
    for(auto i = 0u; i < 4u; ++i)
    {
        normals.emplace_back(0.0f, 1.0f, 0.0f);
    }
    std::vector<glm::vec2> uvs;
    std::vector<unsigned int> indices = {0, 1, 2, 0, 2, 3};

    return DoCreate(
        MeshCategory::Plane,
        MeshPrimitives::Triangles,
        std::move(name),
        std::move(positions),
        std::move(normals),
        std::move(uvs),
        std::move(indices));
}

Mesh3D* MeshManager::CreateSphere(std::string name, uint32_t segments)
{
    if(auto it = Lookup(name); it != m_cache.end())
    {
        ValidateMeshCategory(it->second->GetMeshType().category, MeshCategory::Sphere);
        return it->second.get();
    }

    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;
    std::vector<unsigned int> indices;

    // top
    positions.emplace_back(0.0f, 1.0f, 0.0f);
    normals.emplace_back(0.0f, 1.0f, 0.0f);

    // middle
    for(auto j = 0u; j < segments - 1; ++j)
    {
        double polarAngle = glm::pi<double>() * double(j + 1) / double(segments); // 0° - 180° divided into segments
        double const sinPolar = std::sin(polarAngle);
        double const cosPolar = std::cos(polarAngle);

        for(auto i = 0u; i < segments; ++i)
        {
            double const azimuth = 2.0 * glm::pi<double>() * double(i) / double(segments); // 0° - 360° divided into segments
            double const sinAzimuth = std::sin(azimuth);
            double const cosAzimuth = std::cos(azimuth);
            glm::vec3 pos(
                static_cast<float>(sinPolar * cosAzimuth),
                static_cast<float>(cosPolar),
                static_cast<float>(sinPolar * sinAzimuth));
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

    return DoCreate(
        MeshCategory::Sphere,
        MeshPrimitives::Triangles,
        std::move(name),
        std::move(positions),
        std::move(normals),
        std::move(uvs),
        std::move(indices));
}

Mesh3D* MeshManager::CreateLineGrid(std::string name, uint32_t width, uint32_t height)
{
    if(auto it = Lookup(name); it != m_cache.end())
    {
        ValidateMeshCategory(it->second->GetMeshType().category, MeshCategory::LineGrid);
        return it->second.get();
    }

    std::vector<glm::vec3> positions, normals;
    std::vector<glm::vec2> uvs;
    std::vector<unsigned int> indices;

    unsigned int count = 0;
    auto const stepY = 2.0f / static_cast<float>(height);
    auto const stepX = 2.0f / static_cast<float>(width);
    for(auto i = 0u; i < width; ++i)
    {
        auto const x = i * stepX - 1.0f;
        positions.emplace_back(x, 0.0f, -1.0f);
        positions.emplace_back(x, 0.0f, 1.0f);
        normals.emplace_back(0.0f, 1.0f, 0.0f);
        normals.emplace_back(0.0f, 1.0f, 0.0f);
        indices.push_back(count++);
        indices.push_back(count++);
    }

    for(auto i = 0u; i < height; ++i)
    {
        auto const y = i * stepY - 1.0f;
        positions.emplace_back(-1.0f, 0.0f, y);
        positions.emplace_back(1.0f, 0.0f, y);
        normals.emplace_back(0.0f, 1.0f, 0.0f);
        normals.emplace_back(0.0f, 1.0f, 0.0f);
        indices.push_back(count++);
        indices.push_back(count++);
    }

    return DoCreate(
        MeshCategory::LineGrid,
        MeshPrimitives::Lines,
        std::move(name),
        std::move(positions),
        std::move(normals),
        std::move(uvs),
        std::move(indices));
}

Mesh3D* MeshManager::CreateTriangleGrid(std::string name, uint32_t width, uint32_t height)
{
    if(auto it = Lookup(name); it != m_cache.end())
    {
        ValidateMeshCategory(it->second->GetMeshType().category, MeshCategory::TriangleGrid);
        return it->second.get();
    }

    std::vector<glm::vec3> positions, normals;
    std::vector<glm::vec2> uvs;
    std::vector<unsigned int> indices;

    unsigned int count = 0;
    auto const stepY = 2.0f / static_cast<float>(height);
    auto const stepX = 2.0f / static_cast<float>(width);
    for(auto j = height; j > 0; --j)
    {
        auto const y = j * stepY - 1.0f;
        for(auto i = 0u; i < width; ++i)
        {
            auto const x = i * stepX - 1.0f;

            positions.emplace_back(x, 0.0f, y);
            positions.emplace_back(x + stepX, 0.0f, y);
            positions.emplace_back(x, 0.0f, y - stepY);
            positions.emplace_back(x + stepX, 0.0f, y);
            positions.emplace_back(x + stepX, 0.0f, y - stepY);
            positions.emplace_back(x, 0.0f, y - stepY);

            for(auto k = 0; k < 6; ++k)
            {
                normals.emplace_back(0.0f, 1.0f, 0.0f);
                indices.push_back(count++);
            }
        }
    }

    return DoCreate(
        MeshCategory::TriangleGrid,
        MeshPrimitives::Triangles,
        std::move(name),
        std::move(positions),
        std::move(normals),
        std::move(uvs),
        std::move(indices));
}

std::vector<Mesh3D*> MeshManager::CreateFromFile(std::string name, std::string filename)
{
    std::vector<Mesh3D*> meshes;
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
    int c = 0;
    for(auto i = 0u; i < scene->mNumMeshes; ++i)
    {
        const aiMesh* mesh = scene->mMeshes[i];
        std::vector<glm::vec3> positions, normals;
        for(auto j = 0u; j < mesh->mNumVertices; ++j)
        {
            auto const& pos = mesh->mVertices[j];
            auto const& normal = mesh->mNormals[j];
            positions.emplace_back(pos.x, pos.y, pos.z);
            normals.emplace_back(normal.x, normal.y, normal.z);
        }

        std::vector<unsigned int> indices;
        for(auto j = 0u; j < mesh->mNumFaces; ++j)
        {
            auto const& face = mesh->mFaces[j];
            indices.push_back(face.mIndices[0]);
            indices.push_back(face.mIndices[1]);
            indices.push_back(face.mIndices[2]);
        }

        std::vector<glm::vec2> uvs;

        std::stringstream ss;
        ss << name << c++;
        meshes.push_back(DoCreate(
            FIRE::MeshCategory::Custom,
            FIRE::MeshPrimitives::Triangles,
            ss.str(),
            std::move(positions),
            std::move(normals),
            std::move(uvs),
            std::move(indices)));
    }
    return meshes;
}

Mesh3D* MeshManager::DoCreate(
    MeshCategory meshCategory,
    MeshPrimitives primitives,
    std::string name,
    std::vector<glm::vec3>&& positions,
    std::vector<glm::vec3>&& normals,
    std::vector<glm::vec2>&& uvs,
    std::vector<unsigned int>&& indices)
{
    auto mesh = std::make_unique<Mesh3D>(name, MeshType(meshCategory, primitives));

    mesh->GetVertexDeclaration().AddSection("vPos", 3u, 0u);
    mesh->GetVertexDeclaration().AddSection("vNormal", 3u, static_cast<uint32_t>(positions.size() * sizeof(float) * 3));
    mesh->GetVertexDeclaration().AddSection("vUV", 2u, static_cast<uint32_t>((positions.size() + normals.size()) * sizeof(float) * 3));

    mesh->AddPositions(std::move(positions));
    mesh->AddNormals(std::move(normals));
    mesh->AddUVs(std::move(uvs));
    mesh->AddIndices(std::move(indices));

    auto retVal = mesh.get();
    m_cache.insert(std::make_pair(name, std::move(mesh)));
    return retVal;
}

std::unordered_map<std::string, std::unique_ptr<Mesh3D>>::const_iterator MeshManager::Lookup(std::string const& name) const
{
    return m_cache.find(name);
}

} // namespace FIRE
