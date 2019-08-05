#include <FIRE/InputComponent.h>

namespace FIRE
{
InputComponent::InputComponent(InputListener& inputListener)
    : inputListener(inputListener)
{
}

InputComponent::~InputComponent() = default;

void InputComponent::Setup(SceneObject&)
{
    // base implementation, do nothing
}

void InputComponent::Update(double deltaTime, SceneObject& sceneObject, Scene& scene)
{
    DoUpdate(deltaTime, sceneObject, scene);
}

} // namespace FIRE
