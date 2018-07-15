#include "fire/vertexData.h"
#include <functional>
#include <glm/glm.hpp>
#include <gtest/gtest.h>

namespace
{
glm::vec3 const DUMMY(1, 2, 3);

template <typename Container>
void ExpectContainerContainsOneOf(
    Container const& container, typename Container::value_type const& value)
{
    ASSERT_EQ(container.size(), 1);
    EXPECT_EQ(container.back(), value);
}

class VertexDataTest : public ::testing::Test
{
public:
    void ExpectDirtyAfterChange(std::function<void(void)> func)
    {
        EXPECT_FALSE(m_vertexData.IsDirty());
        func();
        EXPECT_TRUE(m_vertexData.IsDirty());
    }

protected:
    Fire::VertexData m_vertexData;
};

} // namespace

TEST(VertexDataStandaloneTest, VertexDataCanBeDefaultConstructed)
{
    Fire::VertexData v;
}

TEST_F(VertexDataTest, DefaultConstructedHasNoPositions)
{
    EXPECT_TRUE(m_vertexData.GetPositions().empty());
}

TEST_F(VertexDataTest, DefaultConstructedHasNoNormals)
{
    EXPECT_TRUE(m_vertexData.GetNormals().empty());
}

TEST_F(VertexDataTest, DefaultConstructedHasNoTextureCoords)
{
    EXPECT_TRUE(m_vertexData.GetTexCoords().empty());
}

TEST_F(VertexDataTest, DefaultConstructedHasNoColors)
{
    EXPECT_TRUE(m_vertexData.GetColors().empty());
}

TEST_F(VertexDataTest, IsMarkedDirtyAfterAChangeToItsPositions)
{
    ExpectDirtyAfterChange([&]() { m_vertexData.AddPosition(DUMMY); });
}

TEST_F(VertexDataTest, IsMarkedDirtyAfterAChangeToItsNormals)
{
    ExpectDirtyAfterChange([&]() { m_vertexData.AddNormal(DUMMY); });
}

TEST_F(VertexDataTest, IsMarkedDirtyAfterAChangeToItsTexCoords)
{
    ExpectDirtyAfterChange([&]() { m_vertexData.AddTexCoord(DUMMY); });
}

TEST_F(VertexDataTest, IsMarkedDirtyAfterAChangeToItsColors)
{
    ExpectDirtyAfterChange([&]() { m_vertexData.AddColor(DUMMY); });
}

TEST_F(VertexDataTest, AddedPositionsAreStored)
{
    m_vertexData.AddPosition(DUMMY);
    ExpectContainerContainsOneOf(m_vertexData.GetPositions(), DUMMY);
}

TEST_F(VertexDataTest, AddedNormalsAreStored)
{
    m_vertexData.AddNormal(DUMMY);
    ExpectContainerContainsOneOf(m_vertexData.GetNormals(), DUMMY);
}

TEST_F(VertexDataTest, AddedTexCoordsAreStored)
{
    m_vertexData.AddTexCoord(DUMMY);
    ExpectContainerContainsOneOf(m_vertexData.GetTexCoords(), DUMMY);
}

TEST_F(VertexDataTest, AddedColorsAreStored)
{
    m_vertexData.AddColor(DUMMY);
    ExpectContainerContainsOneOf(m_vertexData.GetColors(), DUMMY);
}

TEST_F(VertexDataTest, DirtyFlagCanBeReset)
{
    EXPECT_FALSE(m_vertexData.IsDirty());
    m_vertexData.AddColor(DUMMY);
    m_vertexData.ClearDirtyFlag();
    EXPECT_FALSE(m_vertexData.IsDirty());
}
