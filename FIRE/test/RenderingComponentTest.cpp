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

    MOCK_METHOD3(DoUpdate, void(double, FIRE::SceneObject&, FIRE::Scene&));
    MOCK_METHOD2(Receive, std::optional<std::any>(FIRE::Message, FIRE::SceneObject&));
};

} // namespace

TEST(ARenderingComponent, CallsItsDerivedDoUpdateFunction)
{
    FIRE::Renderer renderer(nullptr, nullptr, nullptr);

    TestRenderingComponent renderingComponent(renderer);
    EXPECT_CALL(renderingComponent, DoUpdate(_, _, _));

    FIRE::SceneObject obj("");
    FIRE::Scene scene;
    renderingComponent.Update(0.0, obj, scene);
}