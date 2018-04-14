#include <gtest/gtest.h>
#include "glmForward.h"
#include "entity.h"

namespace
{
    class EntityTest : public ::testing::Test
    {
    public:
        EntityTest()
            : m_entity("name")
        {

        }

    
        blocks::Entity m_entity;
    };
}

TEST_F(EntityTest, EntitiesShouldHaveAName)
{
    EXPECT_STREQ(m_entity.GetName().c_str(), "name");
}

TEST_F(EntityTest, NewlyCreatedEntitesShouldBeAtOrigin)
{
    EXPECT_EQ(m_entity.GetTransform().GetPosition(), glm::zero<glm::vec3>());
}

TEST_F(EntityTest, NewlyCreatedEntitiesShouldHaveNoAssetsAssigned)
{
    auto& assets = m_entity.GetAssets();
    ASSERT_TRUE(assets.m_material == nullptr);
    ASSERT_TRUE(assets.m_texture == nullptr);
    ASSERT_TRUE(assets.m_mesh.GetVertices().empty());
    ASSERT_TRUE(assets.m_mesh.GetIndices().empty());
    ASSERT_TRUE(assets.m_mesh.GetNormals().empty());
    ASSERT_TRUE(assets.m_mesh.GetTexCoords().empty());
}