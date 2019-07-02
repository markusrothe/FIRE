#include <FIRE/Material.h>
#include <FIRE/ShaderType.h>
#include <FIRE/glmfwd.h>
#include <any>
#include <gtest/gtest.h>
#include <optional>
#include <type_traits>

TEST(AMaterial, HasAName)
{
    FIRE::Material material("name", 0u);
    EXPECT_EQ("name", material.Name());
}

TEST(AMaterial, HasAnAssociatedShader)
{
    FIRE::Material material("", 42u);
    EXPECT_EQ(42u, material.ShaderId());
}

TEST(AMaterial, HasParametersForItsShaders)
{
    FIRE::Material material("", 0u);
    material.SetShaderParameter("Param", FIRE::ShaderParameterType::MAT4x4, glm::mat4x4(1.0f));
    auto materialParam = material.GetShaderParameter("Param");
    ASSERT_TRUE(materialParam);
    EXPECT_EQ(
        static_cast<std::underlying_type_t<FIRE::ShaderParameterType>>(materialParam.value().first),
        static_cast<std::underlying_type_t<FIRE::ShaderParameterType>>(FIRE::ShaderParameterType::MAT4x4));

    EXPECT_EQ(std::any_cast<glm::mat4x4>(materialParam.value().second), glm::mat4x4(1.0f));
}

TEST(AMaterial, AllowsAccessToAllShaderParameters)
{
    FIRE::Material material("", 0u);
    material.SetShaderParameter("Param", FIRE::ShaderParameterType::MAT4x4, glm::mat4x4(1.0f));
    EXPECT_EQ(1u, material.GetShaderParameters().size());
}