#include "Draw.h"
#include "MaterialBinder.h"
#include "VertexLayoutFactory.h"
#include <FIRE/Message.h>
#include <FIRE/Renderer.h>
#include <FIRE/RenderingComponent.h>
#include <FIRE/Scene.h>
#include <FIRE/SceneObject.h>
#include <FIRE/TextOverlay.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace
{
using testing::_;
class TestRenderingComponent : public FIRE::RenderingComponent
{
public:
    explicit TestRenderingComponent(FIRE::Renderer& renderer)
        : FIRE::RenderingComponent(renderer)
    {
    }

    std::optional<std::any> Receive(FIRE::Message, FIRE::SceneObject&) override
    {
        return std::nullopt;
    }

    void DoUpdate(double, FIRE::SceneObject&, FIRE::Scene&) override
    {
        updated = true;
    }

    bool updated{false};
};

} // namespace

TEST(ARenderingComponent, CallsItsDerivedDoUpdateFunction)
{
    FIRE::Renderer renderer(nullptr, nullptr, nullptr, nullptr);

    TestRenderingComponent renderingComponent(renderer);

    FIRE::SceneObject obj("");
    FIRE::Scene scene;
    renderingComponent.Update(0.0, obj, scene);
    EXPECT_TRUE(renderingComponent.updated);
}