#include "Utilities.h"
#include "WarningSuppressions.h"
#include <FIRE/Mesh3D.h>
#include <FIRE/MeshManager.h>
#include <functional>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdexcept>

namespace
{
std::string const NAME{"mesh_name"};

class AMeshManager : public ::testing::Test
{
public:
    FIRE::MeshManager meshManager;
};

} // namespace

using TestUtil::EXPECT_VEC_EQ;

TEST_F(AMeshManager, CreatesACube)
{
    FIRE::MeshHandle mesh = meshManager.CreateCube(NAME);
    FIRE::Mesh3D* cube = meshManager.Lookup(mesh);
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
    FIRE::MeshHandle mesh = meshManager.CreatePlane(NAME);
    auto planeMesh = meshManager.Lookup(mesh);
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
    auto const meshHandle = meshManager.CreateSphere(NAME, numSegments);
    auto const mesh = meshManager.Lookup(meshHandle);
    ASSERT_TRUE(mesh);
    EXPECT_EQ(14u, mesh->Positions().size());
    EXPECT_EQ(14u, mesh->Normals().size());
    EXPECT_EQ(72u, mesh->Indices().size());
}

TEST_F(AMeshManager, CreatesALineGrid)
{
    auto const meshHandle = meshManager.CreateLineGrid(NAME, 10, 10);
    auto const mesh = meshManager.Lookup(meshHandle);
    ASSERT_TRUE(mesh);
    EXPECT_EQ(40u, mesh->Positions().size());
    EXPECT_EQ(40u, mesh->Normals().size());
    EXPECT_EQ(40u, mesh->Indices().size());
}

TEST_F(AMeshManager, CreatesATriangleGrid)
{
    auto const meshHandle = meshManager.CreateTriangleGrid(NAME, 10, 10);
    auto const mesh = meshManager.Lookup(meshHandle);
    ASSERT_TRUE(mesh);
    EXPECT_EQ(600u, mesh->Positions().size());
    EXPECT_EQ(600u, mesh->Normals().size());
    EXPECT_EQ(600u, mesh->Indices().size());
}

TEST_F(AMeshManager, ThrowsIfADifferentMeshTypeIsCreatedWithTheSameName)
{
    auto const mesh = meshManager.CreateCube(NAME);
    EXPECT_THROW(meshManager.CreatePlane(NAME), std::runtime_error);
}

namespace
{
using MeshCreationFunc = std::function<FIRE::MeshHandle(FIRE::MeshManager&)>;
class MeshManagerCachingTest : public testing::TestWithParam<MeshCreationFunc>
{
public:
    FIRE::MeshManager meshManager;
};

// clang-format off
SUPPRESS_UnusedFunction
std::ostream& operator<<(std::ostream& os, MeshCreationFunc const&)
{
    static int i = 0;
    os << i++;
    return os;
}
SUPPRESS_Pop
// clang-format on

} // namespace
TEST_P(MeshManagerCachingTest, CachesACreatedMesh)
{
    auto func = GetParam();
    auto const meshHandle1 = func(meshManager);
    auto const meshHandle2 = func(meshManager);

    auto const mesh1 = meshManager.Lookup(meshHandle1);
    auto const mesh2 = meshManager.Lookup(meshHandle2);

    EXPECT_EQ(mesh1, mesh2);
}
INSTANTIATE_TEST_SUITE_P(
    MeshManagerCachingParamTest,
    MeshManagerCachingTest,
    ::testing::Values(
        [](FIRE::MeshManager& meshManager) { return meshManager.CreateCube(NAME); },
        [](FIRE::MeshManager& meshManager) { return meshManager.CreateSphere(NAME, 10); },
        [](FIRE::MeshManager& meshManager) { return meshManager.CreatePlane(NAME); },
        [](FIRE::MeshManager& meshManager) { return meshManager.CreateLineGrid(NAME, 2, 2); },
        [](FIRE::MeshManager& meshManager) { return meshManager.CreateTriangleGrid(NAME, 2, 2); },
        [](FIRE::MeshManager& meshManager) { return meshManager.Create(
                                                 FIRE::MeshCategory::Custom,
                                                 FIRE::MeshPrimitives::Points,
                                                 NAME, std::vector<glm::vec3>(),
                                                 std::vector<glm::vec3>(), std::vector<unsigned int>()); }));