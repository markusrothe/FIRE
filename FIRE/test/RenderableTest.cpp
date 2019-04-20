#include <FIRE/Mesh.h>
#include <FIRE/Renderable.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace
{
std::string const name{"Renderable"};

class ARenderable : public ::testing::Test
{
public:
    FIRE::Renderable renderable{name};
};

} // namespace

TEST_F(ARenderable, HasAName)
{
    EXPECT_EQ(name, renderable.Name());
}

TEST_F(ARenderable, HasAMesh)
{
    std::string const meshName{"triangleMesh"};
    renderable.SetMesh(FIRE::Mesh(meshName));
    auto const mesh = renderable.GetMesh();
    EXPECT_EQ(meshName, mesh.Name());
}

TEST_F(ARenderable, HasADefaultMaterial)
{
    EXPECT_EQ(std::string("Default"), renderable.GetMaterial());
}

TEST_F(ARenderable, CanBeComparedViaItsName)
{
    FIRE::Renderable other{name};
    EXPECT_EQ(renderable, other);

    FIRE::Renderable different{"DifferentRenderable"};
    EXPECT_NE(renderable, different);
}

TEST_F(ARenderable, HasUniformsToSendToAShader)
{
    renderable.SetShaderUniformMat4x4("MVP", FIRE::Matrix4x4());
    auto const shaderUniform = renderable.GetShaderUniformMat4x4();
    EXPECT_EQ("MVP", shaderUniform.first);
    EXPECT_EQ(FIRE::Matrix4x4(), shaderUniform.second);
}
