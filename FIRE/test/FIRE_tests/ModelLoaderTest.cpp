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
    ASSERT_THAT(loader.GetPositions(0u), SizeIs(24u));
    ASSERT_THAT(loader.GetPositions(0u), Contains(glm::vec3(-0.5f, -0.5f, 0.5f)));
}

TEST_F(AModelLoader, LoadsNormals)
{
    ASSERT_THAT(loader.GetNormals(0u), SizeIs(24u));
    ASSERT_THAT(loader.GetNormals(0u), Contains(glm::vec3(0.0f, 0.0f, 1.0f)));
}

TEST_F(AModelLoader, LoadsTextureCoordinates)
{
    ASSERT_THAT(loader.GetTextureCoordinates(0u), SizeIs(24u));
    ASSERT_THAT(loader.GetTextureCoordinates(0u), Contains(glm::vec2(1.0f, 0.0f)));
}

TEST_F(AModelLoader, LoadsIndices)
{
    ASSERT_THAT(loader.GetIndices(0u), SizeIs(36u));
    ASSERT_THAT(loader.GetIndices(0u), Contains(17u));
}

TEST_F(AModelLoader, LoadsMultipleMeshes)
{
    ASSERT_THAT(loader.GetNumMeshes(), Eq(2u));
    ASSERT_THAT(loader.GetPositions(1u), SizeIs(24u));
    ASSERT_THAT(loader.GetNormals(1u), SizeIs(24u));
    ASSERT_THAT(loader.GetTextureCoordinates(1u), SizeIs(24u));
    ASSERT_THAT(loader.GetIndices(1u), SizeIs(36u));
}

TEST_F(AModelLoader, ThrowsIfAGivenMeshIndexIsNotValid)
{
    ASSERT_ANY_THROW((void)loader.GetPositions(2u));
    ASSERT_ANY_THROW((void)loader.GetNormals(2u));
    ASSERT_ANY_THROW((void)loader.GetTextureCoordinates(2u));
    ASSERT_ANY_THROW((void)loader.GetIndices(2u));
    ASSERT_ANY_THROW((void)loader.GetTexture(2u));
}

TEST_F(AModelLoader, LoadsTextureFileNames)
{
    ASSERT_THAT(loader.GetTexture(0u), Eq(""));
}