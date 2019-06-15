#include <FIRE/Material.h>
#include <FIRE/Matrix.h>
#include <FIRE/ShaderType.h>
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
    material.SetShaderParameter("Param", FIRE::ShaderParameterType::MAT4x4, FIRE::Matrix4x4());
    auto materialParam = material.GetShaderParameter("Param");
    ASSERT_TRUE(materialParam);
    EXPECT_EQ(
        static_cast<std::underlying_type_t<FIRE::ShaderParameterType>>(materialParam.value().first),
        static_cast<std::underlying_type_t<FIRE::ShaderParameterType>>(FIRE::ShaderParameterType::MAT4x4));

    EXPECT_EQ(std::any_cast<FIRE::Matrix4x4>(materialParam.value().second), FIRE::Matrix4x4());
}

TEST(AMaterial, AllowsAccessToAllShaderParameters)
{
    FIRE::Material material("", 0u);
    material.SetShaderParameter("Param", FIRE::ShaderParameterType::MAT4x4, FIRE::Matrix4x4());
    EXPECT_EQ(1u, material.GetShaderParameters().size());
}