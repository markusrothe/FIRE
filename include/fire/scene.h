#ifndef fire_scene_h
#define fire_scene_h

#include <functional>
#include <string>
#include <vector>

namespace Fire
{
class SceneComponent;
class Renderable;

class Scene
{
public:
    explicit Scene(std::string const& sceneName);

    std::string GetName() const;

    void AddSceneComponent(SceneComponent* sceneComponent);
    SceneComponent* GetSceneComponent(std::string const& name) const;
    unsigned int GetNumOfSceneComponents() const;

    void Update();
    std::vector<Renderable*> GetRenderables() const;

private:
    std::vector<SceneComponent*> m_sceneComponents;
    std::string const m_name;
};
} // namespace Fire

#endif // fire_scene_h
