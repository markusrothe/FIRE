#include "Utilities.h"
#include <FIRE/Mesh3D.h>
#include <FIRE/MeshManager.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdexcept>

namespace
{
std::string const CUBE{"cube"};
std::string const PLANE{"plane"};
std::string const SPHERE("sphere");

class AMeshManager : public ::testing::Test
{
public:
    FIRE::MeshManager meshManager;
};

} // namespace

using TestUtil::EXPECT_VEC_EQ;

TEST_F(AMeshManager, CreatesACube)
{
    FIRE::MeshHandle mesh = meshManager.CreateCube(CUBE);
    FIRE::Mesh3D* cube = meshManager.Lookup3D(mesh);
    ASSERT_TRUE(cube);

    auto const positions = cube->Positions();
    ASSERT_EQ(24u, positions.size());

    auto const normals = cube->Normals();
    ASSERT_EQ(24u, normals.size());

    std::vector<unsigned int> const expectedIndices = {
        11, 3, 17, 11, 17, 13,  // front
        4, 7, 18, 4, 18, 15,    // right
        8, 1, 23, 8, 23, 20,    // back
        2, 10, 12, 2, 12, 21,   // left
        14, 16, 19, 14, 19, 22, // top
        0, 6, 5, 0, 5, 9        // down
    };

    EXPECT_THAT(cube->Indices(), ::testing::ContainerEq(expectedIndices));
}

TEST_F(AMeshManager, CreatesAPlane)
{
    FIRE::MeshHandle mesh = meshManager.CreatePlane(PLANE);
    auto planeMesh = meshManager.Lookup3D(mesh);
    ASSERT_TRUE(planeMesh);

    auto const positions = planeMesh->Positions();
    ASSERT_EQ(4u, positions.size());
    EXPECT_VEC_EQ(positions[0], glm::vec3(-1.0f, 0.0f, -1.0f));
    EXPECT_VEC_EQ(positions[1], glm::vec3(-1.0f, 0.0f, 1.0f));
    EXPECT_VEC_EQ(positions[2], glm::vec3(1.0f, 0.0f, 1.0f));
    EXPECT_VEC_EQ(positions[3], glm::vec3(1.0f, 0.0f, -1.0f));

    auto const normals = planeMesh->Normals();
    ASSERT_EQ(4u, normals.size());
    for(auto i = 0u; i < 4u; ++i)
    {
        EXPECT_VEC_EQ(normals[i], glm::vec3(0.0f, 1.0f, 0.0f));
    }

    std::vector<unsigned int> const expectedIndices = {0, 1, 2, 0, 2, 3};
    EXPECT_THAT(planeMesh->Indices(), ::testing::ContainerEq(expectedIndices));
}

TEST_F(AMeshManager, CreatesASphere)
{
    auto const numSegments = 4;
    auto const meshHandle = meshManager.CreateSphere(SPHERE, numSegments);
    auto const mesh = meshManager.Lookup3D(meshHandle);
    ASSERT_TRUE(mesh);
    EXPECT_EQ(14u, mesh->Positions().size());
    EXPECT_EQ(14u, mesh->Normals().size());
    EXPECT_EQ(72u, mesh->Indices().size());
}

// TEST_F(AMeshManager, Creates2DRectangles)
// {
//     auto const meshHandle = meshManager.Create2DRect("2d_rect", 0, 0, 10, 10);
//     auto const mesh = meshManager.Lookup(meshHandle);
//     ASSERT_TRUE(mesh);
// }

TEST_F(AMeshManager, CachesACreatedMesh)
{
    auto const meshHandle1 = meshManager.CreateCube(CUBE);
    auto const meshHandle2 = meshManager.CreateCube(CUBE);

    auto mesh1 = meshManager.Lookup3D(meshHandle1);
    auto mesh2 = meshManager.Lookup3D(meshHandle2);

    EXPECT_EQ(mesh1, mesh2);
}

TEST_F(AMeshManager, ThrowsIfADifferentMeshTypeIsCreatedWithTheSameName)
{
    auto const mesh = meshManager.CreateCube(CUBE);

    EXPECT_THROW(meshManager.CreatePlane(CUBE), std::runtime_error);
}
