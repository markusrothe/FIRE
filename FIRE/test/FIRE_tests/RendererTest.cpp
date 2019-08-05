#include "Draw.h"
#include "FIRE/TextureManager.h"
#include "FontLoader.h"
#include "MaterialBinder.h"
#include "TextureFactoryMock.h"
#include "VertexLayout.h"
#include "VertexLayoutFactory.h"
#include <FIRE/Renderable.h>
#include <FIRE/Renderer.h>
#include <FIRE/TextOverlay.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace
{
using ::testing::_;
using ::testing::ReturnRef;

class DrawMock : public FIRE::Draw
{
public:
    MOCK_METHOD0(Clear, void(void));
    MOCK_METHOD3(DoDraw, void(FIRE::VertexLayout&, FIRE::MeshPrimitives, uint32_t));
    MOCK_METHOD3(DoDrawIndexed, void(FIRE::VertexLayout&, FIRE::MeshPrimitives, uint32_t));
    MOCK_METHOD0(ToggleWireframe, void(void));
};

class MaterialBinderMock : public FIRE::MaterialBinder
{
public:
    MOCK_METHOD1(Bind, void(FIRE::Material&));
    MOCK_METHOD0(Release, void(void));
};

class VertexLayoutFactoryMock : public FIRE::VertexLayoutFactory
{
public:
    MOCK_METHOD1(CreateStaticIndexedLayout, FIRE::VertexLayout&(FIRE::Renderable const&));
    MOCK_METHOD1(CreateDynamicLayout, FIRE::VertexLayout&(FIRE::TextOverlay const&));
};

class VertexLayoutStub : public FIRE::VertexLayout
{
public:
    VertexLayoutStub()
        : FIRE::VertexLayout(FIRE::DrawMode::INDEXED)
    {
    }
    void BindLayout() override
    {
    }
    void ReleaseLayout() override
    {
    }
    void BufferData(uint32_t, void*) override
    {
    }
    void BufferIndexData(uint32_t, void*) override
    {
    }
    void BufferSubData(uint32_t, uint32_t, void*) override
    {
    }
    void AddVertexAttribute(uint32_t, uint32_t, uint32_t) override
    {
    }
};

class FontLoaderMock : public FIRE::FontLoader
{
public:
    MOCK_METHOD1(LoadChar, FIRE::FontCharacter(char));
};

class ARenderer : public ::testing::Test
{
public:
    FIRE::Renderer CreateRenderer()
    {
        std::unique_ptr<FIRE::TextureManager> texManager = std::make_unique<FIRE::TextureManager>(std::move(texFactory), std::move(fontLoader));
        return FIRE::Renderer(std::move(draw), std::move(matBinder), std::move(vertLayoutFactory), std::move(texManager));
    }

    std::unique_ptr<DrawMock> draw = std::make_unique<DrawMock>();
    std::unique_ptr<MaterialBinderMock> matBinder = std::make_unique<MaterialBinderMock>();
    std::unique_ptr<VertexLayoutFactoryMock> vertLayoutFactory = std::make_unique<VertexLayoutFactoryMock>();
    std::unique_ptr<FIRE_tests::TextureFactoryMock> texFactory = std::make_unique<FIRE_tests::TextureFactoryMock>();
    std::unique_ptr<FontLoaderMock> fontLoader = std::make_unique<FontLoaderMock>();

    VertexLayoutStub layout;
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
    EXPECT_CALL(*fontLoader, LoadChar(_)).Times(3); // 'text' contains 't' 2 times
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