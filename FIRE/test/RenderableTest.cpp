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
    EXPECT_EQ(name, renderable.GetName());
}

TEST_F(ARenderable, HasAMesh)
{
    std::string const meshName{"triangleMesh"};
    renderable.SetMesh(FIRE::Mesh(meshName));
    EXPECT_EQ(meshName, renderable.GetMesh().Name());
}

TEST_F(ARenderable, HasADefaultMaterial)
{
    EXPECT_EQ(std::string("Default"), renderable.GetMaterial());
}
