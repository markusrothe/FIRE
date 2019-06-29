#include "Utilities.h"
#include <FIRE/Mesh.h>
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
    FIRE::Mesh* cube = meshManager.Lookup(mesh);
    ASSERT_TRUE(cube);

    auto const positions = cube->Positions();
    ASSERT_EQ(24u, positions.size());
    EXPECT_VEC_EQ(positions[0], FIRE::Vector3(-1.0f, -1.0f, -1.0f));
    EXPECT_VEC_EQ(positions[1], FIRE::Vector3(-1.0f, -1.0f, -1.0f));
    EXPECT_VEC_EQ(positions[2], FIRE::Vector3(-1.0f, -1.0f, -1.0f));

    EXPECT_VEC_EQ(positions[3], FIRE::Vector3(1.0f, -1.0f, 1.0f));
    EXPECT_VEC_EQ(positions[4], FIRE::Vector3(1.0f, -1.0f, 1.0f));
    EXPECT_VEC_EQ(positions[5], FIRE::Vector3(1.0f, -1.0f, 1.0f));

    EXPECT_VEC_EQ(positions[6], FIRE::Vector3(1.0f, -1.0f, -1.0f));
    EXPECT_VEC_EQ(positions[7], FIRE::Vector3(1.0f, -1.0f, -1.0f));
    EXPECT_VEC_EQ(positions[8], FIRE::Vector3(1.0f, -1.0f, -1.0f));

    EXPECT_VEC_EQ(positions[9], FIRE::Vector3(-1.0f, -1.0f, 1.0f));
    EXPECT_VEC_EQ(positions[10], FIRE::Vector3(-1.0f, -1.0f, 1.0f));
    EXPECT_VEC_EQ(positions[11], FIRE::Vector3(-1.0f, -1.0f, 1.0f));

    EXPECT_VEC_EQ(positions[12], FIRE::Vector3(-1.0f, 1.0f, 1.0f));
    EXPECT_VEC_EQ(positions[13], FIRE::Vector3(-1.0f, 1.0f, 1.0f));
    EXPECT_VEC_EQ(positions[14], FIRE::Vector3(-1.0f, 1.0f, 1.0f));

    EXPECT_VEC_EQ(positions[15], FIRE::Vector3(1.0f, 1.0f, 1.0f));
    EXPECT_VEC_EQ(positions[16], FIRE::Vector3(1.0f, 1.0f, 1.0f));
    EXPECT_VEC_EQ(positions[17], FIRE::Vector3(1.0f, 1.0f, 1.0f));

    EXPECT_VEC_EQ(positions[18], FIRE::Vector3(1.0f, 1.0f, -1.0f));
    EXPECT_VEC_EQ(positions[19], FIRE::Vector3(1.0f, 1.0f, -1.0f));
    EXPECT_VEC_EQ(positions[20], FIRE::Vector3(1.0f, 1.0f, -1.0f));

    EXPECT_VEC_EQ(positions[21], FIRE::Vector3(-1.0f, 1.0f, -1.0f));
    EXPECT_VEC_EQ(positions[22], FIRE::Vector3(-1.0f, 1.0f, -1.0f));
    EXPECT_VEC_EQ(positions[23], FIRE::Vector3(-1.0f, 1.0f, -1.0f));

    auto const normals = cube->Normals();
    ASSERT_EQ(24u, normals.size());
    EXPECT_VEC_EQ(normals[0], FIRE::Vector3(0.0f, -1.0f, 0.0f)); // down
    EXPECT_VEC_EQ(normals[1], FIRE::Vector3(0.0f, 0.0f, -1.0f)); // back
    EXPECT_VEC_EQ(normals[2], FIRE::Vector3(-1.0f, 0.0f, 0.0f)); // left

    EXPECT_VEC_EQ(normals[3], FIRE::Vector3(0.0f, 0.0f, 1.0f));  // front
    EXPECT_VEC_EQ(normals[4], FIRE::Vector3(1.0f, 0.0f, 0.0f));  // right
    EXPECT_VEC_EQ(normals[5], FIRE::Vector3(0.0f, -1.0f, 0.0f)); // down

    EXPECT_VEC_EQ(normals[6], FIRE::Vector3(0.0f, -1.0f, 0.0f)); // down
    EXPECT_VEC_EQ(normals[7], FIRE::Vector3(1.0f, 0.0f, 0.0f));  // right
    EXPECT_VEC_EQ(normals[8], FIRE::Vector3(0.0f, 0.0f, -1.0f)); // back

    EXPECT_VEC_EQ(normals[9], FIRE::Vector3(0.0f, -1.0f, 0.0f));  // down
    EXPECT_VEC_EQ(normals[10], FIRE::Vector3(-1.0f, 0.0f, 0.0f)); // left
    EXPECT_VEC_EQ(normals[11], FIRE::Vector3(0.0f, 0.0f, 1.0f));  // front

    EXPECT_VEC_EQ(normals[12], FIRE::Vector3(-1.0f, 0.0f, 0.0f)); // left
    EXPECT_VEC_EQ(normals[13], FIRE::Vector3(0.0f, 0.0f, 1.0f));  // front
    EXPECT_VEC_EQ(normals[14], FIRE::Vector3(0.0f, 1.0f, 0.0f));  // top

    EXPECT_VEC_EQ(normals[15], FIRE::Vector3(1.0f, 0.0f, 0.0f)); // right
    EXPECT_VEC_EQ(normals[16], FIRE::Vector3(0.0f, 1.0f, 0.0f)); // top
    EXPECT_VEC_EQ(normals[17], FIRE::Vector3(0.0f, 0.0f, 1.0f)); // front

    EXPECT_VEC_EQ(normals[18], FIRE::Vector3(1.0f, 0.0f, 0.0f));  // right
    EXPECT_VEC_EQ(normals[19], FIRE::Vector3(0.0f, 1.0f, 0.0f));  // top
    EXPECT_VEC_EQ(normals[20], FIRE::Vector3(0.0f, 0.0f, -1.0f)); // back

    EXPECT_VEC_EQ(normals[21], FIRE::Vector3(-1.0f, 0.0f, 0.0f)); // left
    EXPECT_VEC_EQ(normals[22], FIRE::Vector3(0.0f, 1.0f, 0.0f));  // top
    EXPECT_VEC_EQ(normals[23], FIRE::Vector3(0.0f, 0.0f, -1.0f)); // back

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
    FIRE::Mesh* planeMesh = meshManager.Lookup(mesh);
    ASSERT_TRUE(planeMesh);

    auto const positions = planeMesh->Positions();
    ASSERT_EQ(4u, positions.size());
    EXPECT_VEC_EQ(positions[0], FIRE::Vector3(-1.0f, 0.0f, -1.0f));
    EXPECT_VEC_EQ(positions[1], FIRE::Vector3(-1.0f, 0.0f, 1.0f));
    EXPECT_VEC_EQ(positions[2], FIRE::Vector3(1.0f, 0.0f, 1.0f));
    EXPECT_VEC_EQ(positions[3], FIRE::Vector3(1.0f, 0.0f, -1.0f));

    auto const normals = planeMesh->Normals();
    ASSERT_EQ(4u, normals.size());
    for(auto i = 0u; i < 4u; ++i)
    {
        EXPECT_VEC_EQ(normals[i], FIRE::Vector3(0.0f, 1.0f, 0.0f));
    }

    std::vector<unsigned int> const expectedIndices = {0, 1, 2, 0, 2, 3};
    EXPECT_THAT(planeMesh->Indices(), ::testing::ContainerEq(expectedIndices));
}

TEST_F(AMeshManager, CreatesASphere)
{
    auto const numSegments = 4;
    auto const mesh = meshManager.CreateSphere(SPHERE, numSegments);
}

TEST_F(AMeshManager, CachesACreatedMesh)
{
    auto const meshHandle1 = meshManager.CreateCube(CUBE);
    auto const meshHandle2 = meshManager.CreateCube(CUBE);

    auto mesh1 = meshManager.Lookup(meshHandle1);
    auto mesh2 = meshManager.Lookup(meshHandle2);

    EXPECT_EQ(mesh1, mesh2);
}

TEST_F(AMeshManager, ThrowsIfADifferentMeshTypeIsCreatedWithTheSameName)
{
    auto const mesh = meshManager.CreateCube(CUBE);

    EXPECT_THROW(meshManager.CreatePlane(CUBE), std::runtime_error);
}