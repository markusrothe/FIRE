#ifndef FIRE_InputComponent_h
#define FIRE_InputComponent_h

#include <FIRE/Component.h>
namespace FIRE
{
class InputListener;
class SceneObject;
class Scene;
class InputComponent : public Component
{
public:
    explicit InputComponent(InputListener& inputListener);
    virtual ~InputComponent();

    void Update(SceneObject& sceneObject, Scene& scene) override;

protected:
    InputListener& inputListener;

private:
    virtual void DoUpdate(SceneObject& sceneObject, Scene& scene) = 0;
};
} // namespace FIRE

#endif // FIRE_InputComponent_h
