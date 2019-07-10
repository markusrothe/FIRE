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
} // namespace FIRE

namespace examples
{

class CubeInputComponent : public FIRE::InputComponent
{
public:
    explicit CubeInputComponent(FIRE::InputListener& inputListener, FIRE::Window& window);

private:
    void Init(FIRE::SceneObject& sceneObject);
    FIRE::Window& window;
    void DoUpdate(double deltaTime, FIRE::SceneObject& sceneObject, FIRE::Scene& scene) override;
    std::optional<std::any> Receive(FIRE::Message msg) override;
};
} // namespace examples

#endif // examples_CubeInputComponent_h