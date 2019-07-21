#ifndef FIRE_Scene_h
#define FIRE_Scene_h

#include <FIRE/SceneObject.h>

#include <any>
#include <list>
#include <memory>
#include <optional>

namespace FIRE
{
class CameraComponent;
class Message;
class Scene
{
public:
    SceneObject& CreateSceneObject(std::string name);

    void Setup();

    void Update(double deltaTime);

    std::optional<std::any> Send(Message msg);

private:
    std::list<SceneObject> m_sceneObjects;
};

} // namespace FIRE

#endif
