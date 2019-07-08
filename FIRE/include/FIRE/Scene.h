#ifndef FIRE_Scene_h
#define FIRE_Scene_h

#include <FIRE/SceneObject.h>

#include <list>
#include <memory>

namespace FIRE
{
class CameraComponent;
class Scene
{
public:
    SceneObject& CreateSceneObject(std::string name);

    void Update();
    //CameraComponent const* GetCamera();

private:
    std::list<SceneObject> m_sceneObjects;
};

} // namespace FIRE

#endif
