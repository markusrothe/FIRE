#include "fire/shader.h"
#include "fire/shaderCompiler.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <memory>
#include <utility>

namespace
{
    std::string const shaderName = "shaderName";

    class ShaderCompilerMock : public Fire::ShaderCompiler
    {
    public:
        MOCK_METHOD0(Compile, int(void));
        MOCK_METHOD0(Link, int(void));
    };    

    class ShaderTest : public ::testing::Test
    {
    public:
        ShaderTest()
            : m_shaderCompilerMock(std::make_unique<::testing::NiceMock<ShaderCompilerMock>>())
            , m_shaderCompilerPtr(m_shaderCompilerMock.get())
            , m_shader(shaderName, nullptr)
        {

        }
             
    protected:
        std::unique_ptr<::testing::NiceMock<ShaderCompilerMock>> m_shaderCompilerMock;
        ShaderCompilerMock* m_shaderCompilerPtr;
        
        Fire::Shader m_shader;
    };
} // namespace


TEST_F(ShaderTest, ShadersAreCompiledOnConstruction)
{
    EXPECT_CALL(*m_shaderCompilerPtr, Compile()).Times(1);

    Fire::Shader shader(shaderName, std::move(m_shaderCompilerMock));
}

TEST_F(ShaderTest, ShadersAreLinkedOnConstruction)
{    
    EXPECT_CALL(*m_shaderCompilerPtr, Link()).Times(1);

    Fire::Shader shader(shaderName, std::move(m_shaderCompilerMock));
}

TEST_F(ShaderTest, ShadersHaveAName)
{
    EXPECT_EQ(m_shader.GetName(), shaderName);
}
