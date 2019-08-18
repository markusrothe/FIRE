#include "DrawMock.h"
#include "MaterialBinderMock.h"
#include "ShaderFactoryMock.h"
#include "TextureFactoryMock.h"
#include "VertexLayout.h"
#include "VertexLayoutFactoryMock.h"
#include "VertexLayoutStub.h"
#include <FIRE/AssetFacade.h>
#include <FIRE/Renderable.h>
#include <FIRE/Renderer.h>
#include <FIRE/TextOverlay.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace
{
using ::testing::_;
using ::testing::ReturnRef;

class ARenderer : public ::testing::Test
{
public:
    FIRE::Renderer CreateRenderer()
    {

        return FIRE::Renderer(std::move(draw), std::move(matBinder), std::move(vertLayoutFactory), std::move(assets));
    }

    std::unique_ptr<FIRE_tests::DrawMock> draw = std::make_unique<FIRE_tests::DrawMock>();
    std::unique_ptr<FIRE_tests::MaterialBinderMock> matBinder = std::make_unique<FIRE_tests::MaterialBinderMock>();
    std::unique_ptr<FIRE_tests::VertexLayoutFactoryMock> vertLayoutFactory = std::make_unique<FIRE_tests::VertexLayoutFactoryMock>();
    std::unique_ptr<FIRE_tests::TextureFactoryMock> texFactory = std::make_unique<FIRE_tests::TextureFactoryMock>();
    std::unique_ptr<FIRE_tests::ShaderFactoryMock> shaderFactory = std::make_unique<FIRE_tests::ShaderFactoryMock>();
    std::shared_ptr<FIRE::AssetFacade> assets = std::make_shared<FIRE::AssetFacade>(std::move(texFactory), std::move(shaderFactory));
    FIRE_tests::VertexLayoutStub layout;
    FIRE::Mesh3D mesh{"mesh", FIRE::MeshType()};
};

} // namespace

TEST_F(ARenderer, BindsAndReleasesAMaterialWhenDrawingRenderables)
{
    EXPECT_CALL(*vertLayoutFactory, CreateStaticIndexedLayout(_))
        .WillOnce(ReturnRef(layout));

    {
        ::testing::InSequence sequenceGuard;
        EXPECT_CALL(*matBinder, Bind(_));
        EXPECT_CALL(*draw, DoDrawIndexed(_, _, _));
        EXPECT_CALL(*matBinder, Release());
    }
    auto renderer = CreateRenderer();
    renderer.Submit(FIRE::Renderable("renderable", FIRE::Material(), &mesh));
    renderer.Render(800.0f, 600.0f);
}

TEST_F(ARenderer, DrawsRenderables)
{
    EXPECT_CALL(*vertLayoutFactory, CreateStaticIndexedLayout(_))
        .WillOnce(ReturnRef(layout));
    EXPECT_CALL(*draw, DoDrawIndexed(_, _, _));
    auto renderer = CreateRenderer();
    renderer.Submit(FIRE::Renderable("renderable", FIRE::Material(), &mesh));
    renderer.Render(800.0f, 600.0f);
}

TEST_F(ARenderer, DrawsTextOverlays)
{
    EXPECT_CALL(*vertLayoutFactory, CreateDynamicLayout(_)).WillOnce(ReturnRef(layout));
    EXPECT_CALL(*draw, DoDraw(_, _, _)).Times(4);
    auto renderer = CreateRenderer();
    renderer.Submit(FIRE::TextOverlay("overlay", "text", 0.0f, 0.0f, FIRE::Material()));
    renderer.Render(800.0f, 600.0f);
}

TEST_F(ARenderer, AllowsToToggleWireframeMode)
{
    EXPECT_CALL(*draw, ToggleWireframe());
    auto renderer = CreateRenderer();
    renderer.ToggleWireframe();
}