//#include "ShaderFactoryMock.h"
//#include "Texture2DStub.h"
//#include "TextureFactoryMock.h"
//#include <FIRE/AssetFacade.h>
//#include <FIRE/RenderableBuilder.h>
//#include <gmock/gmock.h>
//#include <gtest/gtest.h>
//
//using namespace testing;
//namespace
//{
//class ARenderableBuilder : public Test
//{
//public:
//    ARenderableBuilder()
//        : textureFactory{std::make_unique<FIRE_tests::TextureFactoryMock>()}
//        , textureFactoryMock{*textureFactory}
//        , shaderFactory{std::make_unique<FIRE_tests::ShaderFactoryMock>()}
//        , shaderFactoryMock{*shaderFactory}
//        , assets(std::move(textureFactory), std::move(shaderFactory))
//    {
//    }
//
//    std::unique_ptr<FIRE_tests::TextureFactoryMock> textureFactory;
//    FIRE_tests::TextureFactoryMock& textureFactoryMock;
//
//    std::unique_ptr<FIRE_tests::ShaderFactoryMock> shaderFactory;
//    FIRE_tests::ShaderFactoryMock& shaderFactoryMock;
//
//    FIRE::AssetFacade assets;
//    std::string NAME{"name"};
//};
//} // namespace
//
//TEST_F(ARenderableBuilder, CreatesRenderablesWithANamePrefix)
//{
//    FIRE::RenderableBuilder builder(assets, NAME, 1u);
//    auto const renderables = builder.Build();
//    ASSERT_THAT(renderables, SizeIs(1u));
//    ASSERT_THAT(renderables[0].name.substr(0, NAME.size()), Eq(NAME));
//}
//
//TEST_F(ARenderableBuilder, CreatesMultipleRenderables)
//{
//    auto const renderables = assets.CreateRenderables(NAME, 2u).Build();
//    ASSERT_THAT(renderables, SizeIs(2u));
//    ASSERT_THAT(renderables[0].name.substr(NAME.size(), NAME.size() + 1), Eq("0"));
//    ASSERT_THAT(renderables[1].name.substr(NAME.size(), NAME.size() + 1), Eq("1"));
//}
//
//TEST_F(ARenderableBuilder, CreatesRenderablesWithoutMeshesPerDefault)
//{
//    auto const renderables = assets.CreateRenderables(NAME, 1u).Build();
//    ASSERT_THAT(renderables[0].mesh, IsNull());
//}
//
//TEST_F(ARenderableBuilder, CreatesRenderablesWithTheDefaultMaterialPerDefault)
//{
//    auto const renderables = assets.CreateRenderables(NAME, 1u).Build();
//    ASSERT_THAT(renderables[0].material.Name(), Eq("Default"));
//}
//
//TEST_F(ARenderableBuilder, CreatesRenderablesWithAMesh)
//{
//    assets.CreateMesh(NAME, FIRE::MeshCategory::Cube);
//    auto const renderables = assets.CreateRenderables(NAME, 1u)
//                                 .WithMesh(NAME)
//                                 .Build();
//    ASSERT_TRUE(renderables[0].mesh);
//}
//
//TEST_F(ARenderableBuilder, CreatesRenderablesWithAMeshAndTextures)
//{
//    assets.CreateMesh(NAME, FIRE::MeshCategory::Cube);
//    assets.SubmitTexture(NAME, std::make_unique<FIRE_tests::Texture2DStub>(42u));
//
//    auto const renderables = assets.CreateRenderables(NAME, 1u)
//                                 .WithMesh(NAME)
//                                 .WithTexture(NAME, 0u)
//                                 .Build();
//
//    ASSERT_THAT(renderables[0].material.GetTexture(0u), Eq(assets.GetTexture(NAME)));
//}
//
//TEST_F(ARenderableBuilder, CreatesRenderablesWithANewMesh)
//{
//    auto const renderables = assets.CreateRenderables(NAME, 1u)
//                                 .WithMesh(NAME, FIRE::MeshCategory::Cube)
//                                 .Build();
//    ASSERT_TRUE(assets.GetMesh(NAME));
//}
//
//TEST_F(ARenderableBuilder, CreatesMultipleRenderablesWithDifferentMeshes)
//{
//    auto const renderables = assets.CreateRenderables(NAME, 3u)
//                                 .WithMesh(NAME + "cube", FIRE::MeshCategory::Cube)
//                                 .WithMesh(NAME + "plane", FIRE::MeshCategory::Plane)
//                                 .WithMesh(NAME + "sphere", FIRE::MeshCategory::Sphere)
//                                 .Build();
//
//    ASSERT_THAT(renderables, SizeIs(3u));
//    ASSERT_THAT(renderables[0].mesh->Name(), Eq(NAME + "cube"));
//    ASSERT_THAT(renderables[1].mesh->Name(), Eq(NAME + "plane"));
//    ASSERT_THAT(renderables[2].mesh->Name(), Eq(NAME + "sphere"));
//    ASSERT_THAT(renderables[0].mesh->Positions(), SizeIs(24u));
//    ASSERT_THAT(renderables[1].mesh->Positions(), SizeIs(4u));
//    ASSERT_THAT(renderables[2].mesh->Positions(), SizeIs(382u));
//}
//
//TEST_F(ARenderableBuilder, ThrowsIfMoreMeshesThanRenderablesHaveBeenSpecified)
//{
//    ASSERT_ANY_THROW(assets.CreateRenderables(NAME, 1u)
//                         .WithMesh(NAME)
//                         .WithMesh(NAME)
//                         .Build());
//}
//
//TEST_F(ARenderableBuilder, CreatesRenderablesWithMaterials)
//{
//    EXPECT_CALL(shaderFactoryMock, Create(_))
//        .WillOnce(Return(42u))
//        .WillOnce(Return(43u));
//
//    assets.SubmitShaders("TestMaterial1", {});
//    assets.SubmitShaders("TestMaterial2", {});
//    auto const renderables = assets.CreateRenderables(NAME, 2u)
//                                 .WithMaterial("TestMaterial1")
//                                 .WithMaterial("TestMaterial2")
//                                 .Build();
//
//    ASSERT_THAT(renderables[0].material.Name(), Eq("TestMaterial1"));
//    ASSERT_THAT(renderables[0].material.ShaderId(), Eq(42u));
//
//    ASSERT_THAT(renderables[1].material.Name(), Eq("TestMaterial2"));
//    ASSERT_THAT(renderables[1].material.ShaderId(), Eq(43u));
//}
//
//TEST_F(ARenderableBuilder, ThrowsIfMoreMaterialsThanRenderablesHaveBeenSpecified)
//{
//    ASSERT_ANY_THROW(assets.CreateRenderables(NAME, 1u)
//                         .WithMaterial("Default")
//                         .WithMaterial("Default")
//                         .Build());
//}
//
//TEST_F(ARenderableBuilder, CreatesRenderablesWithMaterialsAndAssignedTextures)
//{
//    EXPECT_CALL(textureFactoryMock, Load(_, _))
//        .WillOnce(Return(ByMove(std::make_unique<FIRE_tests::Texture2DStub>(42u))))
//        .WillOnce(Return(ByMove(std::make_unique<FIRE_tests::Texture2DStub>(43u))));
//
//    assets.SubmitTexture("Tex1", "", FIRE::Texture2D::WrappingMode::WRAP);
//    assets.SubmitTexture("Tex2", "", FIRE::Texture2D::WrappingMode::WRAP);
//    auto const renderables = assets.CreateRenderables(NAME, 2u)
//                                 .WithMaterial("TestMaterial1")
//                                 .WithMaterial("TestMaterial2")
//                                 .WithTexture("Tex1", 0u)
//                                 .WithTexture("Tex2", 0u)
//                                 .Build();
//
//    ASSERT_THAT(renderables[0].material.GetTexture(0u)->Id(), Eq(42u));
//    ASSERT_THAT(renderables[1].material.GetTexture(0u)->Id(), Eq(43u));
//}
//
//TEST_F(ARenderableBuilder, CreatesRenderablesWithNewTextures)
//{
//    EXPECT_CALL(textureFactoryMock, Load(_, _))
//        .WillOnce(Return(ByMove(std::make_unique<FIRE_tests::Texture2DStub>(42u))))
//        .WillOnce(Return(ByMove(std::make_unique<FIRE_tests::Texture2DStub>(43u))));
//    auto const renderables = assets.CreateRenderables(NAME, 2u)
//                                 .WithNewTexture("Tex1", "filepath", FIRE::Texture2D::WrappingMode::WRAP, 0u)
//                                 .WithNewTexture("Tex2", "filepath", FIRE::Texture2D::WrappingMode::WRAP, 0u)
//                                 .Build();
//    ASSERT_TRUE(assets.GetTexture("Tex1"));
//    ASSERT_TRUE(assets.GetTexture("Tex2"));
//    ASSERT_THAT(renderables[0].material.GetTexture(0u)->Id(), Eq(42u));
//    ASSERT_THAT(renderables[1].material.GetTexture(0u)->Id(), Eq(43u));
//}
//
//TEST_F(ARenderableBuilder, CreatesRenderablesWithMultipleTextureAddedToOneMaterial)
//{
//    EXPECT_CALL(textureFactoryMock, Load(_, _))
//        .WillOnce(Return(ByMove(std::make_unique<FIRE_tests::Texture2DStub>(42u))))
//        .WillOnce(Return(ByMove(std::make_unique<FIRE_tests::Texture2DStub>(43u))));
//    assets.SubmitTexture("Tex1", "", FIRE::Texture2D::WrappingMode::WRAP);
//    assets.SubmitTexture("Tex2", "", FIRE::Texture2D::WrappingMode::WRAP);
//
//    auto const renderables = assets.CreateRenderables(NAME, 2u)
//                                 .WithTextures({{"Tex1", 0u}, {"Tex2", 1u}})
//                                 .Build();
//
//    ASSERT_THAT(renderables[0].material.GetTexture(0u)->Id(), Eq(42u));
//    ASSERT_THAT(renderables[0].material.GetTexture(1u)->Id(), Eq(43u));
//    ASSERT_THAT(renderables[1].material.GetTextures(), IsEmpty());
//}
//
//TEST_F(ARenderableBuilder, CreatesRenderablesWithMultipleTexturesAddedToMultipleMaterials)
//{
//    EXPECT_CALL(textureFactoryMock, Load(_, _))
//        .WillOnce(Return(ByMove(std::make_unique<FIRE_tests::Texture2DStub>(42u))))
//        .WillOnce(Return(ByMove(std::make_unique<FIRE_tests::Texture2DStub>(43u))))
//        .WillOnce(Return(ByMove(std::make_unique<FIRE_tests::Texture2DStub>(44u))))
//        .WillOnce(Return(ByMove(std::make_unique<FIRE_tests::Texture2DStub>(45u))));
//    assets.SubmitTexture("Tex1", "", FIRE::Texture2D::WrappingMode::WRAP);
//    assets.SubmitTexture("Tex2", "", FIRE::Texture2D::WrappingMode::WRAP);
//    assets.SubmitTexture("Tex3", "", FIRE::Texture2D::WrappingMode::WRAP);
//    assets.SubmitTexture("Tex4", "", FIRE::Texture2D::WrappingMode::WRAP);
//
//    auto const renderables = assets.CreateRenderables(NAME, 2u)
//                                 .WithTextures({{"Tex1", 0u}, {"Tex2", 1u}})
//                                 .WithTextures({{"Tex3", 0u}, {"Tex4", 1u}})
//                                 .Build();
//
//    ASSERT_THAT(renderables[0].material.GetTexture(0u)->Id(), Eq(42u));
//    ASSERT_THAT(renderables[0].material.GetTexture(1u)->Id(), Eq(43u));
//    ASSERT_THAT(renderables[1].material.GetTexture(0u)->Id(), Eq(44u));
//    ASSERT_THAT(renderables[1].material.GetTexture(1u)->Id(), Eq(45u));
//}