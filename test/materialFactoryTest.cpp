#include "materialFactory.h"
#include "material.h"
#include "shaderCompiler.h"
#include "shaderLinker.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

namespace
{
class ShaderCompilerMock : public Fire::ShaderCompiler
{
public:
    MOCK_METHOD0(Compile, int(void));
};

class ShaderLinkerMock : public Fire::ShaderLinker
{
public:
    MOCK_METHOD0(Link, int(void));
};

class MaterialFactoryTest : public ::testing::Test
{
public:
    MaterialFactoryTest()
        : m_vertexShaderCompiler()
        , m_fragmentShaderCompiler()
        , m_shaderLinker()
    {
    }

protected:
    ShaderCompilerMock m_vertexShaderCompiler;
    ShaderCompilerMock m_fragmentShaderCompiler;
    ShaderLinkerMock m_shaderLinker;
};
} // namespace

TEST_F(MaterialFactoryTest, CompilesShader)
{
    EXPECT_CALL(m_vertexShaderCompiler, Compile()).Times(1);
    EXPECT_CALL(m_fragmentShaderCompiler, Compile()).Times(1);
    CreateMaterial(
        &m_vertexShaderCompiler, &m_fragmentShaderCompiler, &m_shaderLinker);
}

TEST_F(MaterialFactoryTest, LinksShader)
{
    EXPECT_CALL(m_shaderLinker, Link()).Times(1);
    CreateMaterial(
        &m_vertexShaderCompiler, &m_fragmentShaderCompiler, &m_shaderLinker);
}

TEST_F(MaterialFactoryTest, NeitherLinksNorCompilesIfAnyParamIsNull)
{
    EXPECT_CALL(m_vertexShaderCompiler, Compile()).Times(0);
    EXPECT_CALL(m_fragmentShaderCompiler, Compile()).Times(0);
    EXPECT_CALL(m_shaderLinker, Link()).Times(0);

    CreateMaterial(nullptr, &m_fragmentShaderCompiler, &m_shaderLinker);
    CreateMaterial(&m_vertexShaderCompiler, nullptr, &m_shaderLinker);
    CreateMaterial(&m_vertexShaderCompiler, &m_fragmentShaderCompiler, nullptr);
}
