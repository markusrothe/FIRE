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

TEST_F(ARenderable, CanBeAssignedANewName)
{
    std::string const newName{"newName"};
    renderable.SetName(newName);
    EXPECT_EQ(newName, renderable.Name());
}

TEST_F(ARenderable, HasAMesh)
{
    std::string const meshName{"triangleMesh"};
    renderable.SetMesh(FIRE::Mesh(meshName));

    EXPECT_EQ(meshName, renderable.GetMesh().Name());

    auto const& constRenderable = renderable;
    EXPECT_EQ(meshName, constRenderable.GetMesh().Name());
}

TEST_F(ARenderable, CanBeComparedViaItsName)
{
    FIRE::Renderable other{name};
    EXPECT_EQ(renderable, other);

    FIRE::Renderable different{"DifferentRenderable"};
    EXPECT_NE(renderable, different);
}

TEST_F(ARenderable, HasATransform)
{
    FIRE::Vector3 const zero;
    EXPECT_EQ(zero, renderable.GetTransform().Position());
}

TEST_F(ARenderable, MayBeAssignedAMaterial)
{
    std::string const materialName{"name"};
    auto const shaderId{0u};
    renderable.SetMaterial(FIRE::Material(materialName, shaderId));
    EXPECT_EQ(materialName, renderable.GetMaterial().Name());
    EXPECT_EQ(shaderId, renderable.GetMaterial().ShaderId());

    auto const& constRenderable = renderable;
    EXPECT_EQ(materialName, constRenderable.GetMaterial().Name());
    EXPECT_EQ(shaderId, constRenderable.GetMaterial().ShaderId());
}
