#include "fire/material.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <utility>

namespace
{
std::string const name = "materialName";

class MaterialTest : public ::testing::Test
{
public:
    MaterialTest()
        : m_material(name, 0)
    {
    }

protected:
    Fire::Material m_material;
};
} // namespace

TEST_F(MaterialTest, HasAName) { EXPECT_EQ(m_material.GetName(), name); }

/*
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
*/
