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
class UploaderMock : public FIRE::Uploader
{
public:
    MOCK_METHOD1(Upload, std::tuple<unsigned int, unsigned int, unsigned int>(FIRE::Renderable const&));
};

class UploaderStub : public FIRE::Uploader
{
public:
    std::tuple<unsigned int, unsigned int, unsigned int>
    Upload(FIRE::Renderable const&) override
    {
        return std::make_tuple(0, 0, 0);
    }
};

class DrawAgentMock : public FIRE::DrawAgent
{
public:
    MOCK_METHOD2(Draw, void(FIRE::Renderable const&, std::tuple<unsigned int, unsigned int, unsigned int>));
};

class DrawAgentStub : public FIRE::DrawAgent
{
public:
    void Draw(FIRE::Renderable const&, std::tuple<unsigned int, unsigned int, unsigned int>) override
    {
    }
};

class ARenderer : public ::testing::Test
{
public:
    ARenderer()
        : renderable(std::make_shared<FIRE::Renderable>(""))
    {
        auto sceneComponent = scene.NewSceneComponent("");
        sceneComponent->AddRenderable(renderable);
    }

    std::shared_ptr<FIRE::Renderable> renderable;
    FIRE::Scene scene;
};

} // namespace

TEST_F(ARenderer, UploadsRenderableToGPU)
{
    auto uploader = std::make_unique<UploaderMock>();

    EXPECT_CALL(*uploader, Upload(*renderable));
    FIRE::RendererImpl renderer(
        std::move(uploader), std::make_unique<DrawAgentStub>());

    renderer.Render(scene);
}

TEST_F(ARenderer, RendersAScene)
{
    auto drawAgent = std::make_unique<DrawAgentMock>();
    EXPECT_CALL(*drawAgent, Draw(*renderable, ::testing::_));

    FIRE::RendererImpl renderer{std::make_unique<UploaderStub>(),
                                std::move(drawAgent)};

    renderer.Render(scene);
}
