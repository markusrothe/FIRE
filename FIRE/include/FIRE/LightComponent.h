#ifndef FIRE_LightComponent_h
#define FIRE_LightComponent_h
#include <FIRE/Component.h>
#include <FIRE/glmfwd.h>

namespace FIRE
{
class SceneObject;
class Scene;
class LightComponent : public Component
{
public:
    virtual ~LightComponent() override;
    void Update(double deltaTime, SceneObject& sceneObject, Scene& scene) override;

private:
    virtual void DoUpdate(double deltaTime, SceneObject& sceneObject, Scene& scene) = 0;
};
} // namespace FIRE

#endif // FIRE_LightComponent_h