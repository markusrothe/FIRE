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
    auto const mesh = meshManager.CreateCube(NAME);
    ASSERT_TRUE(mesh);

    auto const positions = mesh->Positions();
    ASSERT_EQ(24u, positions.size());

    auto const normals = mesh->Normals();
    ASSERT_EQ(24u, normals.size());

    auto const indices = mesh->Indices();
    ASSERT_EQ(36u, indices.size());
}

TEST_F(AMeshManager, CreatesAPlane)
{
    auto const mesh = meshManager.CreatePlane(NAME);
    ASSERT_TRUE(mesh);

    auto const positions = mesh->Positions();
    ASSERT_EQ(4u, positions.size());
    EXPECT_VEC_EQ(positions[0], glm::vec3(-1.0f, 0.0f, -1.0f));
    EXPECT_VEC_EQ(positions[1], glm::vec3(-1.0f, 0.0f, 1.0f));
    EXPECT_VEC_EQ(positions[2], glm::vec3(1.0f, 0.0f, 1.0f));
    EXPECT_VEC_EQ(positions[3], glm::vec3(1.0f, 0.0f, -1.0f));

    auto const normals = mesh->Normals();
    ASSERT_EQ(4u, normals.size());
    for(auto i = 0u; i < 4u; ++i)
    {
        EXPECT_VEC_EQ(normals[i], glm::vec3(0.0f, 1.0f, 0.0f));
    }

    std::vector<unsigned int> const expectedIndices = {0, 1, 2, 0, 2, 3};
    EXPECT_THAT(mesh->Indices(), ::testing::ContainerEq(expectedIndices));
}

TEST_F(AMeshManager, CreatesASphere)
{
    auto const numSegments = 4;
    auto const mesh = meshManager.CreateSphere(NAME, numSegments);
    ASSERT_TRUE(mesh);
    EXPECT_EQ(14u, mesh->Positions().size());
    EXPECT_EQ(14u, mesh->Normals().size());
    EXPECT_EQ(72u, mesh->Indices().size());
}

TEST_F(AMeshManager, CreatesALineGrid)
{
    auto const mesh = meshManager.CreateLineGrid(NAME, 10, 10);
    ASSERT_TRUE(mesh);
    EXPECT_EQ(40u, mesh->Positions().size());
    EXPECT_EQ(40u, mesh->Normals().size());
    EXPECT_EQ(40u, mesh->Indices().size());
}

TEST_F(AMeshManager, CreatesATriangleGrid)
{
    auto const mesh = meshManager.CreateTriangleGrid(NAME, 10, 10);
    ASSERT_TRUE(mesh);
    EXPECT_EQ(600u, mesh->Positions().size());
    EXPECT_EQ(600u, mesh->Normals().size());
    EXPECT_EQ(600u, mesh->Indices().size());
}

TEST_F(AMeshManager, ThrowsIfADifferentMeshTypeIsCreatedWithTheSameName)
{
    (void)meshManager.CreateCube(NAME);
    EXPECT_THROW(meshManager.CreatePlane(NAME), std::runtime_error);
}

namespace
{
using MeshCreationFunc = std::function<FIRE::Mesh3D*(FIRE::MeshManager&)>;
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
//clang-format on
} // namespace

TEST_P(MeshManagerCachingTest, CachesACreatedMesh)
{
    auto func = GetParam();

    auto const mesh1 = func(meshManager);
    auto const mesh2 = func(meshManager);

    EXPECT_EQ(mesh1, mesh2);
}

SUPPRESS_ZeroVariadicMacroArguments

INSTANTIATE_TEST_CASE_P(
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
                                                 NAME,
                                                 std::vector<glm::vec3>(),
                                                 std::vector<glm::vec3>(),
                                                 std::vector<glm::vec2>(),
                                                 std::vector<unsigned int>()); }));

SUPPRESS_Pop