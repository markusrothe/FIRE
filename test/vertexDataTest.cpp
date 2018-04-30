#include "fire/vertexData.h"
#include <gtest/gtest.h>

TEST(VertexDataTest, VertexDataCanBeDefaultConstructed)
{
    Fire::VertexData vertexData;

    EXPECT_TRUE(vertexData.m_positions.empty());
    EXPECT_TRUE(vertexData.m_normals.empty());
    EXPECT_TRUE(vertexData.m_texCoords.empty());
    EXPECT_TRUE(vertexData.m_colors.empty());
}
