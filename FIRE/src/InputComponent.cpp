#include <FIRE/InputComponent.h>
#include <FIRE/SceneObject.h>
#include <FIRE/Window.h>
#include <InputListener.h>
namespace FIRE
{
InputComponent::InputComponent(Window& window)
    : inputListener(std::make_shared<InputListener>())
{
    window.SetInputListener(inputListener);
}

InputComponent::~InputComponent() = default;

void InputComponent::Setup(SceneObject&)
{
}

void InputComponent::Update(double deltaTime, SceneObject& sceneObject, Scene& scene)
{
    DoUpdate(deltaTime, sceneObject, scene);
}

std::optional<std::any> InputComponent::Receive(FIRE::Message const& msg, FIRE::SceneObject& sceneObject)
{
    switch(msg.id)
    {
    case MessageID::RegisterKeyEvent:
    {
        auto registerMsg = dynamic_cast<FIRE::KeyRegisterMessage const&>(msg);
        auto& transform = sceneObject.GetTransform();
        auto callback = registerMsg.callback;
        inputListener->RegisterKeyEvent(registerMsg.key, registerMsg.action, [&transform, callback]() mutable { callback(transform); });
        break;
    }
    case MessageID::UnregisterKeyEvent:
    {
        // TODO
        break;
    }
    case MessageID::RegisterMouseMoveEvent:
    {
        auto registerMsg = dynamic_cast<FIRE::MouseMoveRegisterMessage const&>(msg);
        inputListener->RegisterMouseEvent(registerMsg.callback);
        break;
    }
    case MessageID::UnregisterMouseMoveEvent:
    {
        inputListener->UnregisterMouseEvent();
        break;
    }
    case MessageID::RegisterMouseButtonEvent:
    {
        auto registerMsg = dynamic_cast<MouseKeyRegisterMessage const&>(msg);
        auto callback = registerMsg.callback;
        auto& transform = sceneObject.GetTransform();
        inputListener->RegisterMouseButtonEvent(registerMsg.key, registerMsg.action, [&transform, callback]() mutable { callback(transform); });
        break;
    }
    case MessageID::UnregisterMouseButtonEvent:
    {
        //TODO
        break;
    }
    default:
        break;
    }
    return std::nullopt;
}

void InputComponent::DoUpdate(double, SceneObject&, Scene&)
{
}

} // namespace FIRE
