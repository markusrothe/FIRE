#include <FIRE/Component.h>
#include <FIRE/Message.h>
#include <FIRE/Scene.h>
#include <any>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <optional>

namespace
{
using ::testing::Return;
auto const messageResponse = 42;
class TestComponent : public FIRE::Component
{
public:
    void Setup(FIRE::SceneObject&) override
    {
    }

    void Update(double, FIRE::SceneObject&, FIRE::Scene&) override
    {
        updated = true;
    }

    std::optional<std::any> Receive(FIRE::Message, FIRE::SceneObject&) override
    {
        return messageResponse;
    }

    bool updated{false};
};

class AScene : public ::testing::Test
{
public:
    FIRE::Scene scene;
};

TEST_F(AScene, CreatesSceneObjectsWithAName)
{
    std::string const name{"obj"};
    auto& obj = scene.CreateSceneObject(name);
    EXPECT_EQ(obj.GetName(), name);
}

TEST_F(AScene, UpdatesSceneObjectsAndThusComponents)
{
    auto& obj = scene.CreateSceneObject("obj");
    auto component = std::make_unique<TestComponent>();
    bool& updated = component->updated; // keep a reference to "component->updated"
    obj.AddComponent(std::move(component));

    scene.Update(0.0);
    EXPECT_TRUE(updated);
}

TEST_F(AScene, BroadcastsMessagesToSceneObjectsAndThusToComponents)
{
    FIRE::Message message(FIRE::MessageID::GetViewMatrix);
    auto& obj = scene.CreateSceneObject("obj");

    auto component = std::make_unique<TestComponent>();
    obj.AddComponent(std::move(component));

    EXPECT_EQ(messageResponse, std::any_cast<int>(scene.Send(message).value()));
}

TEST_F(AScene, MayContainNoComponentOrSceneObjectThatCanHandleAMessage)
{
    auto response = scene.Send(FIRE::Message(FIRE::MessageID::GetViewMatrix));
    EXPECT_FALSE(response);
}

} // namespace
