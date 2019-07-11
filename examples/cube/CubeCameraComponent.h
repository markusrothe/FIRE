#ifndef examples_CubeCameraComponent_h
#define examples_CubeCameraComponent_h

#include <FIRE/CameraComponent.h>

namespace FIRE
{
class SceneObject;
class Scene;
} // namespace FIRE

namespace examples
{

class CubeCameraComponent : public FIRE::CameraComponent
{
public:
    CubeCameraComponent(FIRE::SceneObject& sceneObject, float fovy, float aspect, float near, float far);

    ~CubeCameraComponent() override;

private:
    void DoUpdate(double deltaTime, FIRE::SceneObject& sceneObject, FIRE::Scene& scene) override;
    std::optional<std::any> Receive(FIRE::Message msg) override;
};
} // namespace examples

#endif //examples_CubeCameraComponent_h