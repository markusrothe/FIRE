#include <FIRE/Scene.h>
#include <gtest/gtest.h>
#include <memory>

namespace
{
std::string const sceneComponentName{"component"};
} // namespace

TEST(AScene, CreatesSceneComponents)
{
    FIRE::Scene scene;
    auto sceneComponent = scene.NewSceneComponent(sceneComponentName);

    EXPECT_EQ(sceneComponentName, sceneComponent->Name());
}

TEST(AScene, ContainsSceneComponents)
{
    FIRE::Scene scene;
    scene.NewSceneComponent("component_0");
    scene.NewSceneComponent("component_1");

    EXPECT_EQ(2u, scene.GetSceneComponents().size());
}
