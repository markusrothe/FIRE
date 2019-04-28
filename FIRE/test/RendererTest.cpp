#include "DrawAgent.h"
#include "RendererImpl.h"
#include "Uploader.h"
#include <FIRE/Renderable.h>
#include <FIRE/Scene.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <tuple>

namespace
{
using ::testing::_;
using ::testing::Ref;
class UploaderMock : public FIRE::Uploader
{
public:
    MOCK_METHOD1(Upload, std::tuple<unsigned int, unsigned int, unsigned int>(FIRE::Renderable const&));
};

class DrawAgentMock : public FIRE::DrawAgent
{
public:
    MOCK_METHOD2(Draw, void(FIRE::Renderable const&, std::tuple<unsigned int, unsigned int, unsigned int>));
    MOCK_METHOD0(Clear, void(void));
};

class ARenderer : public ::testing::Test
{
public:
    ARenderer()
        : uploaderPtr(std::make_unique<UploaderMock>())
        , drawAgentPtr(std::make_unique<DrawAgentMock>())
        , uploader(*uploaderPtr)
        , drawAgent(*drawAgentPtr)
        , renderer(std::move(uploaderPtr), std::move(drawAgentPtr))
        , renderable(std::make_shared<FIRE::Renderable>(""))
    {
        auto sceneComponent = scene.NewSceneComponent("");
        sceneComponent->AddRenderable(renderable);
    }

private:
    std::unique_ptr<UploaderMock> uploaderPtr;
    std::unique_ptr<DrawAgentMock> drawAgentPtr;

protected:
    UploaderMock& uploader;
    DrawAgentMock& drawAgent;
    FIRE::RendererImpl renderer;

    FIRE::Scene scene;
    std::shared_ptr<FIRE::Renderable> renderable;
};

} // namespace

TEST_F(ARenderer, UploadsRenderableToGPU)
{
    EXPECT_CALL(uploader, Upload(Ref(*renderable)));
    renderer.Render(scene);
}

TEST_F(ARenderer, RendersAScene)
{
    EXPECT_CALL(drawAgent, Draw(Ref(*renderable), _));
    renderer.Render(scene);
}

TEST_F(ARenderer, DoesNotDoAnythingWithAnEmptyScene)
{
    EXPECT_CALL(uploader, Upload(_)).Times(0);
    EXPECT_CALL(drawAgent, Draw(_, _)).Times(0);

    FIRE::Scene emptyScene;
    renderer.Render(emptyScene);
}

TEST_F(ARenderer, DoesNotDoAnythingWithASceneWithoutRenderables)
{
    EXPECT_CALL(uploader, Upload(_)).Times(0);
    EXPECT_CALL(drawAgent, Draw(_, _)).Times(0);

    FIRE::Scene sceneWithoutRenderables;
    auto sceneComponent = sceneWithoutRenderables.NewSceneComponent("");
    sceneComponent->AddRenderable(nullptr);
    renderer.Render(sceneWithoutRenderables);
}
