#include <FIRE/Component.h>
#include <FIRE/Message.h>
#include <FIRE/Scene.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace
{
using ::testing::Return;
class TestComponent : public FIRE::Component
{
public:
    MOCK_METHOD2(Update, void(FIRE::SceneObject&, FIRE::Scene&));
    MOCK_METHOD1(Receive, std::optional<std::any>(FIRE::Message));
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

TEST_F(AScene, BroadcastsMessagesToSceneObjects)
{
    auto const responseValue = 42;
    FIRE::Message message(0);
    auto& obj = scene.CreateSceneObject("obj");

    auto component = std::make_unique<TestComponent>();
    EXPECT_CALL(*component, Receive(message)).WillOnce(Return(responseValue));
    obj.AddComponent(std::move(component));

    EXPECT_EQ(responseValue, std::any_cast<int>(scene.Send(message).value()));
}

} // namespace
