#include "FontLoader.h"
#include "TextureFactory.h"
#include <FIRE/MeshManager.h>
#include <FIRE/ModelLoader.h>
#include <FIRE/TextureManager.h>
#include <gtest/gtest.h>

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
        "f 5/3/6 1/2/6 3/4/6\n";
};
} // namespace

TEST_F(AModelLoader, LoadsModelsAsRenderables)
{
    FIRE::TextureManager texManager(nullptr, nullptr);
    FIRE::Material mat;
    FIRE::MeshManager meshManager;
    FIRE::ModelLoader loader(meshManager, texManager);
    auto renderables = loader.Load(cubeObj, mat);
    ASSERT_TRUE(!renderables.empty());
    ASSERT_TRUE(renderables[0].mesh);
    EXPECT_EQ(24u, renderables[0].mesh->Positions().size());
    EXPECT_EQ(24u, renderables[0].mesh->Normals().size());
    EXPECT_EQ(24u, renderables[0].mesh->UVs().size());
}