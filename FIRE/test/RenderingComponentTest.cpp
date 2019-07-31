//#include <FIRE/Message.h>
//#include <FIRE/RenderingComponent.h>
//#include <FIRE/Scene.h>
//#include <FIRE/SceneObject.h>
//#include <FIRE/TextOverlay.h>
//#include <RenderableRenderer.h>
//#include <gmock/gmock.h>
//#include <gtest/gtest.h>
//
//namespace
//{
//glm::vec3 const pos{0.0f, 1.0f, 2.0f};
//
//class TestRenderer : public FIRE::RenderableRenderer
//{
//public:
//    ~TestRenderer() override = default;
//
//    void Render(float, float) override
//    {
//    }
//
//    void ToggleWireframe() override
//    {
//    }
//};
//
//class TestRenderingComponent : public FIRE::RenderingComponent
//{
//public:
//    TestRenderingComponent(FIRE::RenderableRenderer& renderer)
//        : FIRE::RenderingComponent(renderer)
//    {
//    }
//
//private:
//    void DoUpdate(double, FIRE::SceneObject& sceneObject, FIRE::Scene&)
//    {
//        sceneObject.GetTransform().SetPosition(pos);
//    }
//
//    std::optional<std::any> Receive(FIRE::Message, FIRE::SceneObject&)
//    {
//        return std::nullopt;
//    }
//};
//} // namespace
//
//TEST(ARenderingComponent, CallsItsDerivedDoUpdateFunction)
//{
//    TestRenderer renderer;
//    TestRenderingComponent renderingComponent(renderer);
//
//    FIRE::SceneObject obj("");
//    FIRE::Scene scene;
//
//    renderingComponent.Update(0.0, obj, scene);
//
//    EXPECT_EQ(pos, obj.GetTransform().Position());
//}