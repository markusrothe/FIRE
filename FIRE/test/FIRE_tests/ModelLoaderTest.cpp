#include "ModelLoader.h"
#include "CubeOBJ.h"
#include "MeshFactory.h"
#include "TextureFactory.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;

namespace
{
class AModelLoader : public ::testing::Test
{
public:
    FIRE::ModelLoader loader{FIRE::ModelLoader::Source::Memory, FIRE_tests::cubeOBJ};
};

} // namespace

TEST_F(AModelLoader, LoadsPositions)
{
    auto const positions = loader.GetModel(0u).mesh->Positions();
    ASSERT_THAT(positions, SizeIs(24u));
    ASSERT_THAT(positions, Contains(glm::vec3(-0.5f, -0.5f, 0.5f)));
}

TEST_F(AModelLoader, LoadsNormals)
{
    auto const normals = loader.GetModel(0u).mesh->Normals();
    ASSERT_THAT(normals, SizeIs(24u));
    ASSERT_THAT(normals, Contains(glm::vec3(0.0f, 0.0f, 1.0f)));
}

TEST_F(AModelLoader, LoadsTextureCoordinates)
{
    auto const textureCoordinates = loader.GetModel(0u).mesh->UVs();
    ASSERT_THAT(textureCoordinates, SizeIs(24u));
    ASSERT_THAT(textureCoordinates, Contains(glm::vec2(1.0f, 0.0f)));
}

TEST_F(AModelLoader, LoadsIndices)
{
    auto const indices = loader.GetModel(0u).mesh->Indices();
    ASSERT_THAT(indices, SizeIs(36u));
    ASSERT_THAT(indices, Contains(17u));
}

TEST_F(AModelLoader, LoadsMultipleMeshes)
{
    ASSERT_THAT(loader.GetNumModels(), Eq(2u));
}

TEST_F(AModelLoader, ThrowsIfAGivenModelIndexIsNotValid)
{
    ASSERT_ANY_THROW((void)loader.GetModel(2u));
}

TEST_F(AModelLoader, LoadsTextures)
{
    auto const tex = loader.GetTexture(0u);
    ASSERT_THAT(tex.first, Eq(""));
    ASSERT_THAT(tex.second, Eq(FIRE::Texture2D::WrappingMode::WRAP));
}

TEST_F(AModelLoader, MayGetItsModelsStolen)
{
    auto model = loader.StealModel(0u);
    ASSERT_THAT(model.mesh->Positions(), SizeIs(24u));
    ASSERT_THAT(loader.GetNumModels(), Eq(1u));
}