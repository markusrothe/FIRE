#include "Texture2DMock.h"
#include <FIRE/Material.h>
#include <FIRE/ShaderType.h>
#include <FIRE/glmfwd.h>
#include <any>
#include <gtest/gtest.h>
#include <optional>
#include <type_traits>

namespace
{
class AMaterial : public ::testing::Test
{
public:
    std::string const NAME{"name"};
    unsigned int SHADER_ID{42u};
    FIRE::Material material{NAME, SHADER_ID};
    FIRE_tests::Texture2DMock tex;
};
} // namespace

TEST_F(AMaterial, HasAName)
{
    EXPECT_EQ(NAME, material.Name());
}

TEST_F(AMaterial, HasAnAssociatedShader)
{
    EXPECT_EQ(SHADER_ID, material.ShaderId());
}

TEST_F(AMaterial, HasParametersForItsShaders)
{
    material.SetShaderParameter("Param", FIRE::ShaderParameterType::MAT4x4, glm::mat4x4(1.0f));
    auto materialParam = material.GetShaderParameter("Param");
    ASSERT_TRUE(materialParam);
    EXPECT_EQ(
        static_cast<std::underlying_type_t<FIRE::ShaderParameterType>>(materialParam.value().first),
        static_cast<std::underlying_type_t<FIRE::ShaderParameterType>>(FIRE::ShaderParameterType::MAT4x4));

    EXPECT_EQ(std::any_cast<glm::mat4x4>(materialParam.value().second), glm::mat4x4(1.0f));
}

TEST_F(AMaterial, MayHaveNoShaderParameters)
{
    EXPECT_FALSE(material.GetShaderParameter("Param"));
}

TEST_F(AMaterial, AllowsAccessToAllShaderParameters)
{
    material.SetShaderParameter("Param", FIRE::ShaderParameterType::MAT4x4, glm::mat4x4(1.0f));
    EXPECT_EQ(1u, material.GetShaderParameters().size());
}

TEST_F(AMaterial, MayHaveTexturesAttachedToATextureSlot)
{
    material.AddTexture(&tex, 0u);
    EXPECT_EQ(&tex, material.GetTexture(0u));
}

TEST_F(AMaterial, ReturnsNullptrIfNoTexturePresentForGivenSlot)
{
    EXPECT_EQ(nullptr, material.GetTexture(1u));
}

TEST_F(AMaterial, AllowsAccessToAllAttachedTextures)
{
    material.AddTexture(&tex, 0u);
    material.AddTexture(&tex, 1u);

    ASSERT_EQ(2u, material.GetTextures().size());
}