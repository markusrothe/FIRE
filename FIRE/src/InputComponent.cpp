#include <FIRE/InputComponent.h>

namespace FIRE
{
InputComponent::InputComponent(InputListener& inputListener)
    : inputListener(inputListener)
{
}

InputComponent::~InputComponent() = default;

void InputComponent::Update(SceneObject& sceneObject, Scene& scene)
{
    DoUpdate(sceneObject, scene);
}

} // namespace FIRE
