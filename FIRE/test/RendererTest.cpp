#include "DrawAgent.h"
#include "RendererImpl.h"
#include "Uploader.h"
#include <FIRE/Renderable.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <tuple>

namespace
{
class UploaderMock : public FIRE::Uploader
{
public:
    MOCK_METHOD1(
        Upload, std::tuple<unsigned int, unsigned int, unsigned int>(
                    FIRE::Renderable const&));
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
    MOCK_METHOD2(
        Draw, void(
                  FIRE::Renderable const&,
                  std::tuple<unsigned int, unsigned int, unsigned int>));
};

class DrawAgentStub : public FIRE::DrawAgent
{
public:
    void Draw(
        FIRE::Renderable const&,
        std::tuple<unsigned int, unsigned int, unsigned int>) override
    {
    }
};
} // namespace

TEST(ARenderer, UploadsRenderableToGPU)
{
    FIRE::Renderable renderable{""};
    auto uploader = std::make_unique<UploaderMock>();

    EXPECT_CALL(*uploader, Upload(renderable));
    FIRE::RendererImpl renderer(
        std::move(uploader), std::make_unique<DrawAgentStub>());

    renderer.Render(renderable);
}

TEST(ARenderer, DrawsARenderable)
{
    FIRE::Renderable renderable{""};
    auto drawAgent = std::make_unique<DrawAgentMock>();
    EXPECT_CALL(*drawAgent, Draw(renderable, ::testing::_));

    FIRE::RendererImpl renderer{std::make_unique<UploaderStub>(),
                                std::move(drawAgent)};
    renderer.Render(renderable);
}
