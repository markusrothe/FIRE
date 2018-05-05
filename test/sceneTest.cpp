#include "fire/scene.h"
#include "fire/sceneComponent.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>

namespace
{
    std::string const sceneName = "test";

    class SceneComponentStub : public Fire::SceneComponent
    {
    public:
        explicit SceneComponentStub(std::string const& name): m_name(name) {}
        virtual std::string GetName() const override { return m_name; }
        virtual void Update() override {}
        virtual std::vector<Fire::Renderable*> GetRenderables() const override { return std::vector<Fire::Renderable*>(); }
        
    private:
        std::string const m_name;
    };

    class SceneComponentMock : public Fire::SceneComponent
    {
    public:
        MOCK_CONST_METHOD0(GetName, std::string());
        MOCK_METHOD0(Update, void());
        MOCK_CONST_METHOD0(GetRenderables, std::vector<Fire::Renderable*>());
    };

    class SceneTest : public ::testing::Test
    {
    public:
        SceneTest()
            : m_scene(sceneName)
            , m_sceneComponentMock()
        {

        }

        Fire::Scene m_scene;
        SceneComponentMock m_sceneComponentMock;
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

TEST_F(SceneTest, SceneComponentsCanBeAddedToScenes)
{
    auto const name = "testName";

    SceneComponentStub sceneComponentStub(name);
    m_scene.AddSceneComponent(&sceneComponentStub);

    EXPECT_EQ(&sceneComponentStub, m_scene.GetSceneComponent(name));
}

TEST_F(SceneTest, NullPtrSceneComponentsAreNotAddedToScenes)
{
    m_scene.AddSceneComponent(nullptr);
    EXPECT_EQ(m_scene.GetNumOfSceneComponents(), 0);
}

TEST_F(SceneTest, ScenesDontHaveSceneComponentsUponCreation)
{
    EXPECT_EQ(m_scene.GetNumOfSceneComponents(), 0);
}

TEST_F(SceneTest, UpdatingASceneUpdatesItsSceneComponents)
{
    m_scene.AddSceneComponent(&m_sceneComponentMock);

    EXPECT_CALL(m_sceneComponentMock, Update()).Times(1);
    m_scene.Update();
}

TEST_F(SceneTest, ScenesCanBeQueriedForRenderablesOfSceneComponents)
{
    m_scene.AddSceneComponent(&m_sceneComponentMock);

    EXPECT_CALL(m_sceneComponentMock, GetRenderables()).Times(1);
    m_scene.GetRenderables();
}
