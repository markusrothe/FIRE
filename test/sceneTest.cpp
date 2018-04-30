#include "fire/scene.h"
#include "fire/sceneComponent.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

namespace
{
    std::string const sceneName = "test";

    class SceneComponentStub : public Fire::SceneComponent
    {
    public:
        explicit SceneComponentStub(std::string const& name): m_name(name) {}
        virtual std::string GetName() const override { return m_name; }
        virtual void Update() override {}
    private:
        std::string const m_name;
    };

    class SceneComponentMock : public Fire::SceneComponent
    {
    public:
        MOCK_CONST_METHOD0(GetName, std::string());
        MOCK_METHOD0(Update, void());
    };

    class SceneTest : public ::testing::Test
    {
    public:
        SceneTest()
            : m_scene(sceneName)
        {

        }

        Fire::Scene m_scene;
    };

} // namespace

TEST_F(SceneTest, ScenesHaveAName)
{
    EXPECT_EQ(m_scene.GetName(), sceneName);
}

TEST(SceneTestStandalone, SceneHaveGenericNamesIfAnEmptyNameIsProvided)
{
    Fire::Scene scene("");

    EXPECT_EQ(scene.GetName(), "scene_generic_0");
}

TEST_F(SceneTest, ScenesContainSceneComponents)
{
    std::string const name = "testName";

    SceneComponentStub sceneComponentStub(name);
    m_scene.AddSceneComponent(&sceneComponentStub);

    EXPECT_EQ(&sceneComponentStub, m_scene.GetSceneComponent(name));
}

TEST_F(SceneTest, NullPtrSceneComponentsAreNotAddedToScenes)
{
    m_scene.AddSceneComponent(nullptr);

    EXPECT_EQ(m_scene.GetSceneComponents().size(), 0u);
}

TEST_F(SceneTest, UpdatingASceneUpdatesItsSceneComponents)
{
    SceneComponentMock sceneComponent;
    m_scene.AddSceneComponent(&sceneComponent);

    EXPECT_CALL(sceneComponent, Update()).Times(1);
    m_scene.Update();
}
