#ifndef examples_InputMappingComponent_h
#define examples_InputMappingComponent_h

#include <FIRE/InputComponent.h>

namespace FIRE
{
class SceneObject;
class Scene;
class InputListener;
class Message;
class Window;
class Renderer;
} // namespace FIRE

namespace examples
{

class InputMappingComponent : public FIRE::InputComponent
{
public:
    explicit InputMappingComponent(
        FIRE::SceneObject& sceneObject,
        FIRE::InputListener& inputListener,
        FIRE::Window& window,
        FIRE::Renderer& renderer);

private:
    void DoUpdate(double deltaTime, FIRE::SceneObject& sceneObject, FIRE::Scene& scene) override;
    std::optional<std::any> Receive(FIRE::Message msg, FIRE::SceneObject& sceneObject) override;
};
} // namespace examples

#endif