#include "DrawAgent.h"
#include "FontTextureFactory.h"
#include "GLRenderer.h"
#include "ImageTextureFactory.h"
#include "TextureFactory.h"
#include "Uploader.h"
#include <FIRE/Renderable.h>
#include <FIRE/Scene.h>
#include <FIRE/TextOverlay.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <tuple>

namespace
{
using ::testing::_;
using ::testing::Ref;
using ::testing::Return;

float constexpr WIDTH = 800.0f;
float constexpr HEIGHT = 600.0f;

class UploaderMock : public FIRE::Uploader
{
public:
    MOCK_METHOD1(Upload, FIRE::GLVertexArrayObject(FIRE::Renderable const&));
};

class DrawAgentMock : public FIRE::DrawAgent
{
public:
    MOCK_METHOD2(Draw, void(FIRE::Renderable const&, FIRE::GLVertexArrayObject));
    MOCK_METHOD0(Clear, void(void));
    MOCK_METHOD0(ToggleWireframe, void(void));
};

class TextureFactoryStub : public FIRE::TextureFactory
{
public:
    TextureFactoryStub()
        : FIRE::TextureFactory(nullptr, nullptr)
    {
    }
};

class ARenderer : public ::testing::Test
{
public:
    ARenderer()
        : uploaderPtr(std::make_unique<UploaderMock>())
        , drawAgentPtr(std::make_unique<DrawAgentMock>())
        , textureFactoryPtr(std::make_unique<TextureFactoryStub>())
        , uploader(*uploaderPtr)
        , drawAgent(*drawAgentPtr)
        , renderer(std::move(uploaderPtr), std::move(drawAgentPtr), std::move(textureFactoryPtr))
        , scene()
    {
    }

private:
    std::unique_ptr<UploaderMock> uploaderPtr;
    std::unique_ptr<DrawAgentMock> drawAgentPtr;
    std::unique_ptr<TextureFactoryStub> textureFactoryPtr;

protected:
    UploaderMock& uploader;
    DrawAgentMock& drawAgent;
    FIRE::GLRenderer renderer;
    FIRE::Scene scene;
    FIRE::Renderable renderable;
    std::vector<FIRE::Renderable> renderables = {renderable};
};

} // namespace

// TODO: Reenable tests
/*
TEST_F(ARenderer, UploadsRenderableToGPU)
{
    renderer.Submit(renderable);

    EXPECT_CALL(uploader, Upload(renderable))
        .WillOnce(Return(FIRE::GLVertexArrayObject(0, 0, 0)));

    renderer.Render(WIDTH, HEIGHT);
}

TEST_F(ARenderer, RendersAScene)
{
    renderer.Submit(renderable);

    ON_CALL(uploader, Upload(_))
        .WillByDefault(Return(FIRE::GLVertexArrayObject(0, 0, 0)));

    EXPECT_CALL(drawAgent, Draw(renderable, _));
    renderer.Render(WIDTH, HEIGHT);
}

TEST_F(ARenderer, DoesNotDoAnythingWithoutSubmittedRenderables)
{
    renderer.Render(WIDTH, HEIGHT);
}


TEST_F(ARenderer, RendersTextOverlays)
{
    FIRE::TextOverlay overlay("", 0.4f, 0.4f);
    std::vector<FIRE::TextOverlay> textOverlays = {overlay};
    ON_CALL(*sceneComponent, CollectTextOverlays).WillByDefault(Return(textOverlays));
    EXPECT_CALL(textRenderer, Render(overlay, _, _));
    renderer.Render(scene, WIDTH, HEIGHT);
}

TEST_F(ARenderer, UsesWindowResolutionWhenRenderingText)
{
    FIRE::TextOverlay overlay("", 0.0f, 0.0f);
    std::vector<FIRE::TextOverlay> textOverlays = {overlay};

    ON_CALL(*sceneComponent, CollectTextOverlays).WillByDefault(Return(textOverlays));

    EXPECT_CALL(textRenderer, Render(_, WIDTH, HEIGHT));
    renderer.Render(scene, WIDTH, HEIGHT);
}*/
