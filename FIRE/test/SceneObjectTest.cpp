#include <FIRE/Component.h>
#include <FIRE/Message.h>
#include <FIRE/Scene.h>
#include <FIRE/SceneObject.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace
{
using ::testing::_;
class ComponentMock : public FIRE::Component
{
public:
    MOCK_METHOD3(Update, void(double, FIRE::SceneObject& sceneObject, FIRE::Scene& scene));

    std::optional<std::any> Receive(FIRE::Message)
    {
        return std::nullopt;
    }
};
} // namespace

TEST(ASceneObject, UpdatesItsComponents)
{
    FIRE::SceneObject obj("name");

    auto component = std::make_unique<ComponentMock>();
    EXPECT_CALL(*component, Update(_, ::testing::Ref(obj), _));
    obj.AddComponent(std::move(component));

    FIRE::Scene scene;
    obj.Update(0.0, scene);
}