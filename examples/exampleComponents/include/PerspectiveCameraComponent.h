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
    PerspectiveCameraComponent(FIRE::SceneObject& sceneObject, float fovy, float aspect, float near, float far);

    ~PerspectiveCameraComponent() override;

private:
    void DoUpdate(double deltaTime, FIRE::SceneObject& sceneObject, FIRE::Scene& scene) override;
    std::optional<std::any> Receive(FIRE::Message msg) override;
};
} // namespace examples

#endif