#ifndef examples_CubeLightComponent_h
#define examples_CubeLightComponent_h

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

class CubeLightComponent : public FIRE::LightComponent
{
private:
    FIRE::Transform m_transform;
    void DoUpdate(FIRE::SceneObject& sceneObject, FIRE::Scene& scene) override;
    std::optional<std::any> Receive(FIRE::Message msg) override;
};
} // namespace examples

#endif // examples_CubeLightComponent_h