#include "FontLoader.h"
#include "TextureFactory.h"
#include <FIRE/MeshManager.h>
#include <FIRE/ModelLoader.h>
#include <FIRE/TextureManager.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;

namespace
{
class AModelLoader : public ::testing::Test
{
public:
    std::string const cubeObj =
        "# cube.obj\n"
        "#\n"
        "\n"
        "mtllib cube.mtl\n"
        "o cube\n"
        "\n"
        "v -0.500000 -0.500000 0.500000\n"
        "v 0.500000 -0.500000 0.500000\n"
        "v -0.500000 0.500000 0.500000\n"
        "v 0.500000 0.500000 0.500000\n"
        "v -0.500000 0.500000 -0.500000\n"
        "v 0.500000 0.500000 -0.500000\n"
        "v -0.500000 -0.500000 -0.500000\n"
        "v 0.500000 -0.500000 -0.500000\n"
        "\n"
        "vt 0.000000 0.000000\n"
        "vt 1.000000 0.000000\n"
        "vt 0.000000 1.000000\n"
        "vt 1.000000 1.000000\n"
        "\n"
        "vn 0.000000 0.000000 1.000000\n"
        "vn 0.000000 1.000000 0.000000\n"
        "vn 0.000000 0.000000 -1.000000\n"
        "vn 0.000000 -1.000000 0.000000\n"
        "vn 1.000000 0.000000 0.000000\n"
        "vn -1.000000 0.000000 0.000000\n"
        "\n"
        "g cube\n"
        "usemtl cube\n"
        "s 1\n"
        "f 1/1/1 2/2/1 3/3/1\n"
        "f 3/3/1 2/2/1 4/4/1\n"
        "s 2\n"
        "f 3/1/2 4/2/2 5/3/2\n"
        "f 5/3/2 4/2/2 6/4/2\n"
        "s 3\n"
        "f 5/4/3 6/3/3 7/2/3\n"
        "f 7/2/3 6/3/3 8/1/3\n"
        "s 4\n"
        "f 7/1/4 8/2/4 1/3/4\n"
        "f 1/3/4 8/2/4 2/4/4\n"
        "s 5\n"
        "f 2/1/5 8/2/5 4/3/5\n"
        "f 4/3/5 8/2/5 6/4/5\n"
        "s 6\n"
        "f 7/1/6 1/2/6 5/3/6\n"
        "f 5/3/6 1/2/6 3/4/6\n"
        "\n"
        "g cube2\n"
        "usemtl cube\n"
        "s 1\n"
        "f 1/1/1 2/2/1 3/3/1\n"
        "f 3/3/1 2/2/1 4/4/1\n"
        "s 2\n"
        "f 3/1/2 4/2/2 5/3/2\n"
        "f 5/3/2 4/2/2 6/4/2\n"
        "s 3\n"
        "f 5/4/3 6/3/3 7/2/3\n"
        "f 7/2/3 6/3/3 8/1/3\n"
        "s 4\n"
        "f 7/1/4 8/2/4 1/3/4\n"
        "f 1/3/4 8/2/4 2/4/4\n"
        "s 5\n"
        "f 2/1/5 8/2/5 4/3/5\n"
        "f 4/3/5 8/2/5 6/4/5\n"
        "s 6\n"
        "f 7/1/6 1/2/6 5/3/6\n"
        "f 5/3/6 1/2/6 3/4/6\n";

    FIRE::ModelLoader loader{FIRE::ModelLoader::Source::Memory, cubeObj};
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
    auto const& model = loader.GetModel(0u);
    ASSERT_THAT(model.texturePath, Eq(""));
    ASSERT_THAT(model.textureWrapping, Eq(FIRE::Texture2D::WrappingMode::WRAP));
}

TEST_F(AModelLoader, MayGetItsModelsStolen)
{
    auto model = loader.StealModel(0u);
    ASSERT_THAT(model.mesh->Positions(), SizeIs(24u));
    ASSERT_THAT(loader.GetNumModels(), Eq(1u));
}