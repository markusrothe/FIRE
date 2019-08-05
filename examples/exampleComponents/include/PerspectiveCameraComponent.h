#ifndef examples_PerspectiveCameraComponent_h
#define examples_PerspectiveCameraComponent_h

#include <FIRE/CameraComponent.h>

namespace FIRE
{
class SceneObject;
class Scene;
} // namespace FIRE

namespace examples
{

class PerspectiveCameraComponent : public FIRE::CameraComponent
{
public:
    PerspectiveCameraComponent(float fovy, float aspect, float near, float far);
    ~PerspectiveCameraComponent() override;

private:
    void Setup(FIRE::SceneObject& sceneObject) override;
    void DoUpdate(double deltaTime, FIRE::SceneObject& sceneObject, FIRE::Scene& scene) override;
    std::optional<std::any> Receive(FIRE::Message msg, FIRE::SceneObject& sceneObject) override;
};
} // namespace examples

#endif