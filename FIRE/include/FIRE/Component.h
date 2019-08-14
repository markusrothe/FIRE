#ifndef FIRE_Component_h
#define FIRE_Component_h

#include <FIRE/Message.h>
#include <any>
#include <optional>
namespace FIRE
{
class SceneObject;
class Scene;
class Component
{
public:
    virtual ~Component() = default;
    virtual void Setup(SceneObject& sceneObject) = 0;
    virtual void Update(double deltaTime, SceneObject& sceneObject, Scene& scene) = 0;
    virtual std::optional<std::any> Receive(Message msg, SceneObject& sceneObject) = 0;
};
} // namespace FIRE

#endif // FIRE_Component_h