#ifndef fire_scene_h
#define fire_scene_h

#include <string>
#include <vector>

namespace Fire
{
    class SceneComponent;

    class Scene
    {
    public:
        explicit Scene(std::string const& sceneName);

        std::string GetName() const;

        void AddSceneComponent(SceneComponent* sceneComponent);
        SceneComponent* GetSceneComponent(std::string const& name) const;
        std::vector<SceneComponent*> const& GetSceneComponents() const;

        void Update();
    private:
        std::vector<SceneComponent*> m_sceneComponents;
        std::string const m_name;
    };
} // namespace Fire

#endif // fire_scene_h
