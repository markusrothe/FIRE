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
    unsigned int CreateDefaultShader() override
    {
        return DEFAULT_MATERIAL_ID;
    }

    MOCK_METHOD1(Create, unsigned int(std::vector<std::pair<FIRE::ShaderType, std::string>> const&));
};
} // namespace

TEST(AMaterialFactory, CreatesMaterialsFromCode)
{
    FakeShaderFactory shaderFactory;

    std::vector<std::pair<FIRE::ShaderType, std::string>> const shaderCode = {
        {FIRE::ShaderType::VERTEX_SHADER, "VertexShaderCode"},
        {FIRE::ShaderType::FRAGMENT_SHADER, "FragmentShaderCode"}};

    EXPECT_CALL(shaderFactory, Create(shaderCode)).WillOnce(Return(CUSTOM_MATERIAL_ID));

    FIRE::Material mat = FIRE::MaterialFactory::Create("name", shaderCode, shaderFactory);
    EXPECT_EQ(CUSTOM_MATERIAL_ID, mat.ShaderId());
}

TEST(AMaterialFactory, CreatesADefaultMaterial)
{
    FakeShaderFactory shaderFactory;
    auto mat = FIRE::MaterialFactory::CreateDefault(shaderFactory);
    EXPECT_EQ(DEFAULT_MATERIAL_ID, mat.ShaderId());
    EXPECT_EQ("Default", mat.Name());
}