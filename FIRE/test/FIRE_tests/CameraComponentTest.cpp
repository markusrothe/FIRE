#include <FIRE/CameraComponent.h>
#include <FIRE/Message.h>
#include <FIRE/Scene.h>
#include <FIRE/SceneObject.h>
#include <gtest/gtest.h>

namespace
{
glm::vec3 const pos{0.0f, 1.0f, 2.0f};
glm::vec3 const lookAt{3.0f, 1.0f, 2.0f};
glm::vec3 const up{0.0f, 1.0f, 0.0f};
class TestCameraComponent : public FIRE::CameraComponent
{
public:
    TestCameraComponent()
        : FIRE::CameraComponent(1.0f, 2.0f, 3.0f, 4.0f)
    {
    }

private:
    void DoUpdate(double, FIRE::SceneObject& sceneObject, FIRE::Scene&) override
    {
        sceneObject.GetTransform().SetPosition(pos);
        sceneObject.GetTransform().SetLookAt(lookAt);
    }

};

class ACameraComponent : public ::testing::Test
{
public:
    TestCameraComponent comp;
    FIRE::SceneObject sceneObject{"obj"};
    FIRE::Scene scene;
};

} // namespace

TEST_F(ACameraComponent, CallsItsDerivedDoUpdateFunction)
{
    comp.Update(0.0, sceneObject, scene);
    EXPECT_EQ(pos, sceneObject.GetTransform().Position());
}

TEST_F(ACameraComponent, UpdatesItsViewMatrix)
{
    comp.Update(0.0, sceneObject, scene);
    auto const viewMatrix = comp.Receive(FIRE::Message(FIRE::MessageID::GetViewMatrix), sceneObject);
    EXPECT_EQ(glm::lookAt(pos, lookAt, up), std::any_cast<glm::mat4x4>(viewMatrix.value()));
}

TEST_F(ACameraComponent, UpdatesItsProjectionMatrix)
{
    comp.Update(0.0, sceneObject, scene);
    auto const projMatrix = comp.Receive(FIRE::Message(FIRE::MessageID::GetProjectionMatrix), sceneObject);
    EXPECT_EQ(glm::perspective(1.0f, 2.0f, 3.0f, 4.0f), std::any_cast<glm::mat4x4>(projMatrix.value()));
}