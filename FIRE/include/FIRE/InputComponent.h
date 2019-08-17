#ifndef FIRE_InputComponent_h
#define FIRE_InputComponent_h

#include <FIRE/Component.h>
#include <FIRE/Key.h>
#include <FIRE/KeyAction.h>
#include <FIRE/MouseKey.h>
#include <functional>
#include <memory>
#include <vector>
namespace FIRE
{
class SceneObject;
class Scene;
class InputListener;
class Transform;
class Window;
class InputComponent : public Component
{
public:
    explicit InputComponent(Window& window);
    ~InputComponent() override;

    void Setup(SceneObject& sceneObject) override;
    void Update(double deltaTime, SceneObject& sceneObject, Scene& scene) override;

    std::optional<std::any> Receive(FIRE::Message const& msg, FIRE::SceneObject& sceneObject) override;

protected:
    std::shared_ptr<InputListener> inputListener;

private:
    virtual void DoUpdate(double deltaTime, SceneObject& sceneObject, Scene& scene);
};
} // namespace FIRE

#endif // FIRE_InputComponent_h
