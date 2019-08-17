#include "Utilities.h"
#include "WarningSuppressions.h"
#include <FIRE/Mesh3D.h>
#include <MeshFactory.h>
#include <functional>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdexcept>

using namespace testing;
namespace
{
std::string const NAME{"mesh_name"};
} // namespace

using TestUtil::EXPECT_VEC_EQ;

TEST(AMeshFactory, CreatesACube)
{
    auto const mesh = FIRE::MeshFactory::CreateCube(NAME);
    ASSERT_TRUE(mesh);

    auto const positions = mesh->Positions();
    ASSERT_EQ(24u, positions.size());

    auto const normals = mesh->Normals();
    ASSERT_EQ(24u, normals.size());

    auto const indices = mesh->Indices();
    ASSERT_EQ(36u, indices.size());
}

TEST(AMeshFactory, CreatesAPlane)
{
    auto const mesh = FIRE::MeshFactory::CreatePlane(NAME);
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

TEST(AMeshFactory, CreatesASphere)
{
    auto const numSegments = 4;
    auto const mesh = FIRE::MeshFactory::CreateSphere(NAME, numSegments);
    ASSERT_TRUE(mesh);
    EXPECT_EQ(14u, mesh->Positions().size());
    EXPECT_EQ(14u, mesh->Normals().size());
    EXPECT_EQ(72u, mesh->Indices().size());
}

TEST(AMeshFactory, CreatesALineGrid)
{
    auto const mesh = FIRE::MeshFactory::CreateLineGrid(NAME, 10, 10);
    ASSERT_TRUE(mesh);
    EXPECT_EQ(40u, mesh->Positions().size());
    EXPECT_EQ(40u, mesh->Normals().size());
    EXPECT_EQ(40u, mesh->Indices().size());
}

TEST(AMeshFactory, CreatesATriangleGrid)
{
    auto const mesh = FIRE::MeshFactory::CreateTriangleGrid(NAME, 10, 10);
    ASSERT_TRUE(mesh);
    EXPECT_EQ(600u, mesh->Positions().size());
    EXPECT_EQ(600u, mesh->Normals().size());
    EXPECT_EQ(600u, mesh->Indices().size());
}