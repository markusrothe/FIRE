#include "DrawAgent.h"
#include "RendererImpl.h"
#include "SceneComponentMock.h"
#include "TextRenderer.h"
#include "Uploader.h"
#include <FIRE/Camera.h>
#include <FIRE/Renderable.h>
#include <FIRE/Scene.h>
#include <FIRE/SceneComponent.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <tuple>

namespace
{
using ::testing::_;
using ::testing::Ref;
using ::testing::Return;
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
};

class TextRendererMock : public FIRE::TextRenderer
{
public:
    MOCK_METHOD1(Render, void(FIRE::TextOverlay));
};

class ARenderer : public ::testing::Test
{
public:
    ARenderer()
        : uploaderPtr(std::make_unique<UploaderMock>())
        , drawAgentPtr(std::make_unique<DrawAgentMock>())
        , textRendererPtr(std::make_unique<TextRendererMock>())
        , uploader(*uploaderPtr)
        , drawAgent(*drawAgentPtr)
        , textRenderer(*textRendererPtr)
        , sceneComponent(std::make_shared<Mocks::SceneComponentMock>())
        , renderer(std::move(uploaderPtr), std::move(drawAgentPtr), std::move(textRendererPtr))
        , scene(FIRE::Camera("cam"))
    {
        scene.AddSceneComponent(sceneComponent);
    }

private:
    std::unique_ptr<UploaderMock> uploaderPtr;
    std::unique_ptr<DrawAgentMock> drawAgentPtr;
    std::unique_ptr<TextRendererMock> textRendererPtr;

protected:
    UploaderMock& uploader;
    DrawAgentMock& drawAgent;
    TextRendererMock& textRenderer;
    std::shared_ptr<Mocks::SceneComponentMock> sceneComponent;
    FIRE::RendererImpl renderer;
    FIRE::Scene scene;
    FIRE::Renderable renderable;
    std::vector<FIRE::Renderable> renderables = {renderable};
};

} // namespace

TEST_F(ARenderer, UploadsRenderableToGPU)
{
    ON_CALL(*sceneComponent, CollectRenderables())
        .WillByDefault(Return(renderables));

    EXPECT_CALL(uploader, Upload(renderable))
        .WillOnce(Return(FIRE::GLVertexArrayObject(0, 0, 0)));

    renderer.Render(scene);
}

TEST_F(ARenderer, RendersAScene)
{
    ON_CALL(*sceneComponent, CollectRenderables())
        .WillByDefault(Return(renderables));

    ON_CALL(uploader, Upload(_))
        .WillByDefault(Return(FIRE::GLVertexArrayObject(0, 0, 0)));

    EXPECT_CALL(drawAgent, Draw(renderable, _));
    renderer.Render(scene);
}

TEST_F(ARenderer, DoesNotDoAnythingWithAnEmptyScene)
{
    EXPECT_CALL(uploader, Upload(_)).Times(0);
    EXPECT_CALL(drawAgent, Draw(_, _)).Times(0);

    FIRE::Scene emptyScene(FIRE::Camera(""));
    renderer.Render(emptyScene);
}

TEST_F(ARenderer, DoesNotDoAnythingWithASceneWithoutRenderables)
{
    ON_CALL(*sceneComponent, CollectRenderables())
        .WillByDefault(Return(std::vector<FIRE::Renderable>()));

    EXPECT_CALL(uploader, Upload(_)).Times(0);
    EXPECT_CALL(drawAgent, Draw(_, _)).Times(0);

    renderer.Render(scene);
}

TEST_F(ARenderer, RendersTextOverlays)
{
    FIRE::TextOverlay overlay("", 0.4f, 0.4f);
    std::vector<FIRE::TextOverlay> textOverlays = {overlay};
    ON_CALL(*sceneComponent, CollectTextOverlays).WillByDefault(Return(textOverlays));
    EXPECT_CALL(textRenderer, Render(overlay));
    renderer.Render(scene);
}
