#include "fire/scene.h"
#include <gtest/gtest.h>
#include <string>

namespace
{
    std::string const sceneName = "test";
    
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

TEST(SceneTest, ScenesHaveAName)
{
    Fire::Scene const scene(sceneName);
    
    EXPECT_EQ(scene.GetName(), sceneName);
}
