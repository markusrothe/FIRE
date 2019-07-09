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
    MOCK_METHOD2(Update, void(FIRE::SceneObject& sceneObject, FIRE::Scene& scene));
    MOCK_METHOD1(Receive, std::optional<std::any>(FIRE::Message));
};
} // namespace

TEST(ASceneObject, UpdatesItsComponents)
{
    FIRE::SceneObject obj("name");

    auto component = std::make_unique<ComponentMock>();
    EXPECT_CALL(*component, Update(::testing::Ref(obj), _));
    obj.AddComponent(std::move(component));

    FIRE::Scene scene;
    obj.Update(scene);
}