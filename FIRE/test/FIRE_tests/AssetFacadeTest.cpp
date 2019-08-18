#include "ShaderFactoryMock.h"
#include "Texture2DStub.h"
#include "TextureFactoryMock.h"
#include <CubeOBJ.h>
#include <FIRE/AssetFacade.h>
#include <FIRE/FontCharacter.h>
#include <FIRE/Mesh3D.h>
#include <FIRE/ShaderType.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>

using namespace ::testing;

namespace
{
class AnAssetFacade : public Test
{
public:
    AnAssetFacade()
        : textureFactory{std::make_unique<FIRE_tests::TextureFactoryMock>()}
        , textureFactoryMock{*textureFactory}
        , shaderFactory{std::make_unique<FIRE_tests::ShaderFactoryMock>()}
        , shaderFactoryMock{*shaderFactory}
        , assets(std::move(textureFactory), std::move(shaderFactory))
    {
    }

    std::string const NAME{"name"};

    std::unique_ptr<FIRE_tests::TextureFactoryMock> textureFactory;
    FIRE_tests::TextureFactoryMock& textureFactoryMock;

    std::unique_ptr<FIRE_tests::ShaderFactoryMock> shaderFactory;
    FIRE_tests::ShaderFactoryMock& shaderFactoryMock;

    FIRE::AssetFacade assets;
};
} // namespace

TEST_F(AnAssetFacade, AllowsToSubmitTexturesByFilename)
{
    EXPECT_CALL(textureFactoryMock, Load("TextureFilePath", _));
    assets.SubmitTexture(NAME, "TextureFilePath", FIRE::Texture2D::WrappingMode::WRAP);
}

TEST_F(AnAssetFacade, CachesTexturesByName)
{
    EXPECT_CALL(textureFactoryMock, Load("TextureFilePath", _))
        .WillOnce(Return(ByMove(std::make_unique<FIRE_tests::Texture2DStub>(42u))));
    assets.SubmitTexture(NAME, "TextureFilePath", FIRE::Texture2D::WrappingMode::WRAP);
    ASSERT_THAT(assets.GetTexture(NAME)->Id(), Eq(42u));
}

TEST_F(AnAssetFacade, ReturnsNullptrIfTextureWasNotFound)
{
    ASSERT_THAT(assets.GetTexture(NAME), IsNull());
}

TEST_F(AnAssetFacade, TakesOwnershipOfTextures)
{
    assets.SubmitTexture(NAME, std::make_unique<FIRE_tests::Texture2DStub>(42u));
    ASSERT_THAT(assets.GetTexture(NAME)->Id(), Eq(42u));
}

TEST_F(AnAssetFacade, DoesNotAddATextureWithTheSameNameTwice)
{
    assets.SubmitTexture(NAME, std::make_unique<FIRE_tests::Texture2DStub>(42u));
    assets.SubmitTexture(NAME, std::make_unique<FIRE_tests::Texture2DStub>(44u));
    ASSERT_THAT(assets.GetTexture(NAME)->Id(), Eq(42u));
}

TEST_F(AnAssetFacade, CreatesNewTextures)
{
    auto const width = 2u;
    auto const height = width;
    std::vector<uint8_t> const data = {0x00, 0xff, 0xaa, 0xbb};
    auto const numComponents = 1;
    auto const wrappingMode = FIRE::Texture2D::WrappingMode::WRAP;
    auto const filter = FIRE::Texture2D::Filter::NEAREST;

    EXPECT_CALL(textureFactoryMock, Create2DTexture(width, height, data, numComponents, wrappingMode, filter));
    assets.CreateTexture(NAME, width, height, data, numComponents, wrappingMode, filter);
}

TEST_F(AnAssetFacade, ThrowsIfATextureIsCreatedThatAlreadyExists)
{
    auto const width = 2u;
    auto const height = width;
    std::vector<uint8_t> const data = {0x00, 0xff, 0xaa, 0xbb};
    auto const numComponents = 1;
    auto const wrappingMode = FIRE::Texture2D::WrappingMode::WRAP;
    auto const filter = FIRE::Texture2D::Filter::NEAREST;

    EXPECT_CALL(textureFactoryMock, Create2DTexture(_, _, _, _, _, _))
        .Times(1);

    assets.CreateTexture(NAME, width, height, data, numComponents, wrappingMode, filter);
    ASSERT_ANY_THROW(assets.CreateTexture(NAME, width, height, data, numComponents, wrappingMode, filter));
}

TEST_F(AnAssetFacade, CreatesTexturesForFontCharacters)
{
    auto const width = 2u;
    auto const height = 2u;
    std::vector<uint8_t> data = {0xff, 0x11, 0x21, 0xab};
    EXPECT_CALL(textureFactoryMock, LoadFontCharacter('A'))
        .WillOnce(Return(ByMove(FIRE::FontCharacter(nullptr, {width, height}, {2u, 2u}, 0, data))));

    EXPECT_CALL(
        textureFactoryMock,
        Create2DTexture(
            width, height, data, 1, FIRE::Texture2D::WrappingMode::CLAMP, FIRE::Texture2D::Filter::NEAREST));
    assets.CreateFontCharacter('A');
}

TEST_F(AnAssetFacade, CachesFontCharacters)
{
    EXPECT_CALL(textureFactoryMock, LoadFontCharacter(_)).Times(1);
    EXPECT_CALL(textureFactoryMock, Create2DTexture(_, _, _, _, _, _)).Times(1);
    assets.CreateFontCharacter('A');
    assets.CreateFontCharacter('A');
}

TEST_F(AnAssetFacade, StoresADefaultMaterial)
{
    ASSERT_THAT(assets.GetMaterial("Default").Name(), Eq("Default"));
}

TEST_F(AnAssetFacade, StoresADefaultTextMaterial)
{
    ASSERT_THAT(assets.GetMaterial("TextDefault").Name(), Eq("TextDefault"));
}

TEST_F(AnAssetFacade, AllowsToSubmitShaders)
{
    EXPECT_CALL(shaderFactoryMock, Create(_));
    FIRE::Shaders shaders{{FIRE::ShaderType::VERTEX_SHADER, "shaderCode"}};
    assets.SubmitShaders(NAME, shaders);
}

TEST_F(AnAssetFacade, DoesNotAddTheSameMaterialTwice)
{
    EXPECT_CALL(shaderFactoryMock, Create(_)).Times(1);

    FIRE::Shaders shaders{{FIRE::ShaderType::VERTEX_SHADER, "shaderCode"}};
    assets.SubmitShaders(NAME, shaders);
    assets.SubmitShaders(NAME, shaders);
}

TEST_F(AnAssetFacade, AllowsToSubmitShadersFromFiles)
{
    EXPECT_CALL(shaderFactoryMock, Create(_));
    FIRE::Shaders shaders{{FIRE::ShaderType::VERTEX_SHADER, "shaderCode"}};
    assets.SubmitShadersFromFiles(NAME, shaders);
}

TEST_F(AnAssetFacade, CachesMaterialsByName)
{
    FIRE::Shaders shaders{{FIRE::ShaderType::VERTEX_SHADER, "shaderCode"}};
    assets.SubmitShaders(NAME, shaders);
    ASSERT_THAT(assets.GetMaterial(NAME).Name(), Eq(NAME));
}

TEST_F(AnAssetFacade, AllowsToSubmitModels)
{
    assets.SubmitModel(NAME, FIRE_tests::cubeOBJ);
    ASSERT_THAT(assets.GetModelMeshes(NAME), SizeIs(2));
}

TEST_F(AnAssetFacade, AllowsToSubmitMeshes)
{
    assets.SubmitMesh(NAME, std::make_unique<FIRE::Mesh3D>(NAME, FIRE::MeshType(FIRE::MeshCategory::Custom, FIRE::MeshPrimitives::Triangles)));
    ASSERT_THAT(assets.GetMesh(NAME)->Name(), Eq(NAME));
}

TEST_F(AnAssetFacade, DoesNotAddAMeshWithTheSameNameTwice)
{
    assets.SubmitMesh(NAME, std::make_unique<FIRE::Mesh3D>(NAME, FIRE::MeshType(FIRE::MeshCategory::Custom, FIRE::MeshPrimitives::Triangles)));
    assets.SubmitMesh(NAME, std::make_unique<FIRE::Mesh3D>(NAME, FIRE::MeshType(FIRE::MeshCategory::Plane, FIRE::MeshPrimitives::Triangles)));
    ASSERT_THAT(assets.GetMesh(NAME)->GetMeshType().category, Eq(FIRE::MeshCategory::Custom));
}

TEST_F(AnAssetFacade, CreatesNewBasicMeshes)
{
    assets.CreateMesh("cube", FIRE::MeshCategory::Cube);
    assets.CreateMesh("plane", FIRE::MeshCategory::Plane);
    assets.CreateMesh("sphere", FIRE::MeshCategory::Sphere);
    assets.CreateMesh("triangleGrid", FIRE::MeshCategory::TriangleGrid);
    assets.CreateMesh("lineGrid", FIRE::MeshCategory::LineGrid);

    ASSERT_TRUE(assets.GetMesh("cube"));
    ASSERT_TRUE(assets.GetMesh("plane"));
    ASSERT_TRUE(assets.GetMesh("sphere"));
    ASSERT_TRUE(assets.GetMesh("triangleGrid"));
    ASSERT_TRUE(assets.GetMesh("lineGrid"));
}

TEST_F(AnAssetFacade, AllowsToBuildRenderablesFromModels)
{
    assets.SubmitModel("cube", FIRE_tests::cubeOBJ);
    auto renderables = assets.CreateModelRenderables(NAME, "cube", "material");
    ASSERT_THAT(renderables, SizeIs(2u));
}
