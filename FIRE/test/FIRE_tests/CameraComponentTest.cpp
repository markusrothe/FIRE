#include <FIRE/CameraComponent.h>
#include <FIRE/Message.h>
#include <FIRE/Scene.h>
#include <FIRE/SceneObject.h>
#include <gmock/gmock.h>
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

    std::optional<std::any> Receive(FIRE::Message, FIRE::SceneObject&) override
    {
        return std::nullopt;
    }
};

class ACameraComponent : public ::testing::Test
{
public:
    TestCameraComponent cameraComponent;
    FIRE::SceneObject sceneObject{"obj"};
    FIRE::Scene scene;
};

} // namespace

TEST_F(ACameraComponent, CallsItsDerivedDoUpdateFunction)
{
    cameraComponent.Update(0.0, sceneObject, scene);
    EXPECT_EQ(pos, sceneObject.GetTransform().Position());
}

TEST_F(ACameraComponent, UpdatesItsViewMatrix)
{
    cameraComponent.Update(0.0, sceneObject, scene);
    EXPECT_EQ(glm::lookAt(pos, lookAt, up), cameraComponent.GetViewMatrix());
}

TEST_F(ACameraComponent, UpdatesItsProjectionMatrix)
{
    cameraComponent.Update(0.0, sceneObject, scene);
    EXPECT_EQ(glm::perspective(1.0f, 2.0f, 3.0f, 4.0f), cameraComponent.GetProjectionMatrix());
}