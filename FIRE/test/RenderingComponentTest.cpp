#include <FIRE/Renderer.h>
#include <FIRE/RenderingComponent.h>
#include <FIRE/Scene.h>
#include <FIRE/SceneObject.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace
{
glm::vec3 const pos{0.0f, 1.0f, 2.0f};

class TestRenderer : public FIRE::Renderer
{
public:
    ~TestRenderer() override = default;
    void Submit(FIRE::Renderable const&) override
    {
    }

    void Render(float, float) override
    {
    }
};

class TestRenderingComponent : public FIRE::RenderingComponent
{
public:
    TestRenderingComponent(FIRE::Renderer& renderer)
        : FIRE::RenderingComponent(renderer)
    {
    }

private:
    void DoUpdate(FIRE::SceneObject& sceneObject, FIRE::Scene&)
    {
        sceneObject.GetTransform().SetPosition(pos);
    }
};
} // namespace

TEST(ARenderingComponent, CallsItsDerivedDoUpdateFunction)
{
    TestRenderer renderer;
    TestRenderingComponent renderingComponent(renderer);

    FIRE::SceneObject obj("");
    FIRE::Scene scene;

    renderingComponent.Update(obj, scene);

    EXPECT_EQ(pos, obj.GetTransform().Position());
}