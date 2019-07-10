#ifndef FIRE_Component_h
#define FIRE_Component_h

#include <any>
#include <optional>
namespace FIRE
{
class SceneObject;
class Scene;
class Message;
class Component
{
public:
    virtual ~Component() = default;
    virtual void Update(double deltaTime, SceneObject& sceneObject, Scene& scene) = 0;
    virtual std::optional<std::any> Receive(Message msg) = 0;
};
} // namespace FIRE

#endif // FIRE_Component_h