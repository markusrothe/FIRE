#include <FIRE/Mesh.h>
#include <FIRE/MeshFactory.h>

namespace FIRE
{
std::shared_ptr<Mesh> MeshFactory::CreateCube()
{
    auto mesh = std::make_shared<Mesh>("");
    mesh->AddPositions({{-1.0f, -1.0f, -1.0f},
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
                        {-1.0f, 1.0f, -1.0f}});

    mesh->AddNormals({{0.0f, -1.0f, 0.0f},
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
                      {0.0f, 0.0f, -1.0f}});

    mesh->AddIndices({
        11, 3, 17, 11, 17, 13,  // front
        4, 7, 18, 4, 18, 15,    // right
        8, 1, 23, 8, 23, 20,    // back
        2, 10, 12, 2, 12, 21,   // left
        14, 16, 19, 14, 19, 22, // top
        0, 6, 5, 0, 5, 9        // down
    });

    return mesh;
}

std::shared_ptr<Mesh> MeshFactory::CreatePlane()
{
    auto mesh = std::make_shared<Mesh>("");

    mesh->AddPositions({{-1.0f, 0.0f, -1.0f},
                        {-1.0f, 0.0f, 1.0f},
                        {1.0f, 0.0f, 1.0f},
                        {1.0f, 0.0f, -1.0f}});

    for(auto i = 0u; i < 4u; ++i)
    {
        mesh->AddNormal({0.0f, 1.0f, 0.0f});
    }

    mesh->AddIndices({0, 1, 2, 0, 2, 3});
    return mesh;
}

} // namespace FIRE
