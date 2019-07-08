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
    CubeCameraComponent(float fovy, float aspect, float near, float far);

    ~CubeCameraComponent() override;

protected:
    void DoUpdate(FIRE::SceneObject& sceneObject, FIRE::Scene& scene) override;
};
} // namespace examples

#endif //examples_CubeCameraComponent_h