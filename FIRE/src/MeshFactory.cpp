#include <MeshFactory.h>
#include <algorithm>

#include <cmath>
#include <iostream>
#include <sstream>

namespace FIRE::MeshFactory
{

std::unique_ptr<Mesh3D> CreateCube(std::string const& name)
{
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
        name,
        std::move(positions),
        std::move(normals),
        std::move(uvs),
        std::move(indices));
}

std::unique_ptr<Mesh3D> CreatePlane(std::string const& name)
{
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
        name,
        std::move(positions),
        std::move(normals),
        std::move(uvs),
        std::move(indices));
}

std::unique_ptr<Mesh3D> CreateSphere(std::string const& name, uint32_t segments)
{

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
        name,
        std::move(positions),
        std::move(normals),
        std::move(uvs),
        std::move(indices));
}

std::unique_ptr<Mesh3D> CreateLineGrid(std::string const& name, uint32_t width, uint32_t height)
{

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
        name,
        std::move(positions),
        std::move(normals),
        std::move(uvs),
        std::move(indices));
}

std::unique_ptr<Mesh3D> CreateTriangleGrid(std::string const& name, uint32_t width, uint32_t height)
{

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
        name,
        std::move(positions),
        std::move(normals),
        std::move(uvs),
        std::move(indices));
}

std::unique_ptr<Mesh3D> DoCreate(
    MeshCategory meshCategory,
    MeshPrimitives primitives,
    std::string const& name,
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

    return mesh;
}
} // namespace FIRE::MeshFactory
