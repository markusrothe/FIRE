#ifndef examples_CubeInputComponent_h
#define examples_CubeInputComponent_h

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

class CubeInputComponent : public FIRE::InputComponent
{
public:
    explicit CubeInputComponent(
        FIRE::SceneObject& sceneObject,
        FIRE::InputListener& inputListener,
        FIRE::Window& window,
        FIRE::Renderer& renderer);

private:
    void DoUpdate(double deltaTime, FIRE::SceneObject& sceneObject, FIRE::Scene& scene) override;
    std::optional<std::any> Receive(FIRE::Message msg) override;
};
} // namespace examples

#endif // examples_CubeInputComponent_h