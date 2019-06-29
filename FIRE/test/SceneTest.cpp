#include "SceneComponentMock.h"

#include <FIRE/Camera.h>
#include <FIRE/Renderable.h>
#include <FIRE/Scene.h>
#include <FIRE/SceneComponent.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <vector>

namespace
{

class AScene : public ::testing::Test
{
public:
    AScene()
        : cam{"cam"}
        , scene{cam}
        , sceneComponent{std::make_shared<Mocks::SceneComponentMock>()}
    {
        scene.AddSceneComponent(sceneComponent);
    }

    FIRE::Camera cam;
    FIRE::Scene scene;
    std::shared_ptr<Mocks::SceneComponentMock> sceneComponent;
};

} // namespace

TEST_F(AScene, UpdatesSceneComponents)
{
    EXPECT_CALL(*sceneComponent, Update(cam));
    scene.Update();
}

TEST_F(AScene, CollectsRenderablesFromSceneComponents)
{
    std::vector<FIRE::Renderable> renderables;
    renderables.push_back(FIRE::Renderable());
    EXPECT_CALL(*sceneComponent, CollectRenderables())
        .WillOnce(::testing::Return(renderables));

    EXPECT_THAT(scene.CollectRenderables(), ::testing::ContainerEq(renderables));
}
