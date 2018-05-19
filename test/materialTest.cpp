#include "fire/material.h"

#include <gtest/gtest.h>

namespace
{
    std::string const name = "materialName";
    
    class MaterialTest : public ::testing::Test
    {
    public:
        MaterialTest() : m_material(name) {}
                         
    protected:
        Fire::Material m_material;
    };
} // namespace

TEST_F(MaterialTest, HasAName)
{
    EXPECT_EQ(m_material.GetName(), name);
}

TEST(MaterialTestStandalone, HasDefaultNameIfNoneProvided)
{
    Fire::Material mat("");
    EXPECT_EQ(mat.GetName(), "simple");
}

TEST_F(MaterialTest, SupportsBinding)
{    
    m_material.Bind();
    EXPECT_TRUE(m_material.IsBound());
}

TEST_F(MaterialTest, IsUnboundWhenConstructed)
{
    EXPECT_FALSE(m_material.IsBound());
}

TEST_F(MaterialTest, SupportsUnbinding)
{
    m_material.Bind();
    m_material.Unbind();
    EXPECT_FALSE(m_material.IsBound());
}

/*
  ContainsAShader
  DefaultMaterialUsesSimpleShader
  
 */
