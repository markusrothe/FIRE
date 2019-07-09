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
    void Update(FIRE::SceneObject&, FIRE::Scene&) override
    {
    }

    std::optional<std::any> Receive(FIRE::Message) override
    {
        return messageResponse;
    }
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

TEST_F(AScene, BroadcastsMessagesToSceneObjectsAndThusToComponents)
{
    FIRE::Message message(0);
    auto& obj = scene.CreateSceneObject("obj");

    auto component = std::make_unique<TestComponent>();
    obj.AddComponent(std::move(component));

    EXPECT_EQ(messageResponse, std::any_cast<int>(scene.Send(message).value()));
}

} // namespace
