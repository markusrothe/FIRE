#ifndef FIRE_MeshFactoryTest_h
#define FIRE_MeshFactoryTest_h
#include "Utilities.h"
#include <FIRE/Mesh.h>
#include <FIRE/MeshFactory.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using TestUtil::EXPECT_VEC_EQ;

TEST(AMeshFactory, CreatesACube)
{
    FIRE::MeshFactory factory;
    std::shared_ptr<FIRE::Mesh> cube = factory.CreateCube();

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

    ASSERT_EQ(36u, cube->Indices().size());
    std::vector<unsigned int> expectedIndices = {
        11, 3, 17, 11, 17, 13,  // front
        4, 7, 18, 4, 18, 15,    // right
        8, 1, 23, 8, 23, 20,    // back
        2, 10, 12, 2, 12, 21,   // left
        14, 16, 19, 14, 19, 22, // top
        0, 6, 5, 0, 5, 9        // down
    };

    for(auto i = 0u; i < 36; ++i)
    {
        EXPECT_EQ(expectedIndices[i], cube->Indices()[i]);
    }
}

TEST(AMeshFactory, CreatesAPlane)
{
}

TEST(AMeshFactory, CreatesASphere)
{
}

TEST(AMeshFactory, CachesACreatedMesh)
{
}

#endif // FIRE_MeshFactoryTest_h
