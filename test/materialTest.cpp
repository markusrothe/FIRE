#include "fire/material.h"
#include "fire/shader.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <utility>

namespace
{
std::string const name = "materialName";

class ShaderMock : public Fire::Shader
{
public:
    MOCK_METHOD0(Bind, void(void));
    MOCK_METHOD0(Unbind, void(void));
    MOCK_CONST_METHOD0(GetName, std::string const&(void));
    MOCK_CONST_METHOD0(Bound, bool(void));
};

class MaterialTest : public ::testing::Test
{
public:
    MaterialTest()
        : m_shader(std::make_unique<ShaderMock>())
        , m_shaderMock(m_shader.get())
        , m_material(name, std::move(m_shader))
    {
    }

private:
    std::unique_ptr<ShaderMock> m_shader;

protected:
    ShaderMock* m_shaderMock;
    Fire::Material m_material;
};
} // namespace

TEST_F(MaterialTest, HasAName) { EXPECT_EQ(m_material.GetName(), name); }

TEST(MaterialTestStandalone, HasDefaultNameIfNoneProvided)
{
    Fire::Material mat("", nullptr);
    EXPECT_EQ(mat.GetName(), "simple");
}

TEST_F(MaterialTest, SupportsBinding)
{
    EXPECT_CALL(*m_shaderMock, Bound()).WillOnce(::testing::Return(true));

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
