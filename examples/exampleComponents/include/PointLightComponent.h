#ifndef examples_PointLightComponent_h
#define examples_PointLightComponent_h

#include <FIRE/LightComponent.h>
#include <FIRE/Transform.h>

namespace FIRE
{
class SceneObject;
class Scene;
class Message;
} // namespace FIRE

namespace examples
{

class PointLightComponent : public FIRE::LightComponent
{
private:
    void Setup(FIRE::SceneObject& sceneObject);
    void DoUpdate(double deltaTime, FIRE::SceneObject& sceneObject, FIRE::Scene& scene) override;
    std::optional<std::any> Receive(FIRE::Message msg, FIRE::SceneObject& sceneObject) override;
};
} // namespace examples

#endif