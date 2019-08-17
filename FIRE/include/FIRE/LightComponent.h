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
    ~LightComponent() override;
    void Setup(SceneObject& sceneObject) override;
    void Update(double deltaTime, SceneObject& sceneObject, Scene& scene) override;
    std::optional<std::any> Receive(Message const& msg, SceneObject& sceneObject) override;

private:
    virtual void DoUpdate(double deltaTime, SceneObject& sceneObject, Scene& scene);
};
} // namespace FIRE

#endif // FIRE_LightComponent_h