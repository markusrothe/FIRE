#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <FIRE/Material.h>
#include <FIRE/MaterialFactory.h>
#include <FIRE/ShaderFactory.h>
#include <FIRE/ShaderType.h>

namespace
{

using ::testing::Return;
auto const DEFAULT_MATERIAL_ID = 42u;
auto const CUSTOM_MATERIAL_ID = 18u;
class FakeShaderFactory : public FIRE::ShaderFactory
{
public:
    MOCK_METHOD0(CreateDefaultShader, unsigned int(void));
    MOCK_METHOD1(Create, unsigned int(std::vector<std::pair<FIRE::ShaderType, std::string>> const&));
};

class AMaterialFactory : public ::testing::Test
{
public:
    std::vector<std::pair<FIRE::ShaderType, std::string>> const shaderCode = {
        {FIRE::ShaderType::VERTEX_SHADER, "VertexShaderCode"},
        {FIRE::ShaderType::FRAGMENT_SHADER, "FragmentShaderCode"}};
    std::unique_ptr<FakeShaderFactory> shaderFactory{std::make_unique<FakeShaderFactory>()};
};

} // namespace

TEST_F(AMaterialFactory, UsesAShaderFactory)
{
    EXPECT_CALL(*shaderFactory, CreateDefaultShader());

    FIRE::MaterialFactory materialFactory(std::move(shaderFactory));
    materialFactory.CreateDefaultMaterial();
}

TEST_F(AMaterialFactory, CreatesADefaultMaterial)
{
    EXPECT_CALL(*shaderFactory, CreateDefaultShader())
        .WillOnce(Return(DEFAULT_MATERIAL_ID));

    FIRE::MaterialFactory materialFactory(std::move(shaderFactory));

    auto const material = materialFactory.CreateDefaultMaterial();
    EXPECT_EQ(DEFAULT_MATERIAL_ID, material.ShaderId());
    EXPECT_EQ("Default", material.Name());
}

TEST_F(AMaterialFactory, CreatesMaterialsFromShaderCode)
{
    EXPECT_CALL(*shaderFactory, Create(shaderCode))
        .WillOnce(Return(CUSTOM_MATERIAL_ID));

    FIRE::MaterialFactory materialFactory(std::move(shaderFactory));
    auto const material = materialFactory.CreateMaterial("name", shaderCode);
    EXPECT_EQ(CUSTOM_MATERIAL_ID, material.ShaderId());
}

TEST_F(AMaterialFactory, CachesShaders)
{
    EXPECT_CALL(*shaderFactory, Create(shaderCode))
        .Times(1)
        .WillOnce(Return(CUSTOM_MATERIAL_ID));

    FIRE::MaterialFactory materialFactory(std::move(shaderFactory));
    auto const material = materialFactory.CreateMaterial("name", shaderCode);
    auto const sameMaterial = materialFactory.CreateMaterial("name", shaderCode);
    EXPECT_EQ(material, sameMaterial);
}

TEST_F(AMaterialFactory, AllowsToLookupAlreadyCreatedMaterials)
{
    FIRE::MaterialFactory materialFactory(std::move(shaderFactory));
    auto const createdMaterial = materialFactory.CreateMaterial("name", shaderCode);
    auto const lookedUpMaterial = materialFactory.GetMaterial("name");

    EXPECT_EQ(createdMaterial, lookedUpMaterial);
}

TEST_F(AMaterialFactory, ThrowsIfANonExistentMaterialIsLookedUp)
{
    FIRE::MaterialFactory materialFactory(std::move(shaderFactory));
    EXPECT_THROW(materialFactory.GetMaterial("name"), std::logic_error);
}