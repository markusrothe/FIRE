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
} // namespace

TEST(AMaterialFactory, UsesAShaderFactoryToCreateMaterials)
{
    auto shaderFactory = std::make_unique<FakeShaderFactory>();
    EXPECT_CALL(*shaderFactory, CreateDefaultShader());

    FIRE::MaterialFactory materialFactory(std::move(shaderFactory));
    materialFactory.CreateDefaultMaterial();
}

/*TEST(AMaterialFactory, CreatesADefaultMaterial)
{
    FakeShaderFactory shaderFactory;
    auto mat = FIRE::MaterialFactory::CreateDefault(shaderFactory);
    EXPECT_EQ(DEFAULT_MATERIAL_ID, mat.ShaderId());
    EXPECT_EQ("Default", mat.Name());
}

TEST(AMaterialFactory, CreatesMaterialsFromCode)
{
    FakeShaderFactory shaderFactory;

    std::vector<std::pair<FIRE::ShaderType, std::string>> const shaderCode = {
        {FIRE::ShaderType::VERTEX_SHADER, "VertexShaderCode"},
        {FIRE::ShaderType::FRAGMENT_SHADER, "FragmentShaderCode"}};

    EXPECT_CALL(shaderFactory, Create(shaderCode)).WillOnce(Return(CUSTOM_MATERIAL_ID));

    FIRE::Material mat = FIRE::MaterialFactory::Create("name", shaderCode, shaderFactory);
    EXPECT_EQ(CUSTOM_MATERIAL_ID, mat.ShaderId());
}*/
