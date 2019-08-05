#include "InputMappingComponent.h"
#include <FIRE/InputListener.h>
#include <FIRE/Message.h>
#include <FIRE/Renderer.h>
#include <FIRE/Scene.h>
#include <FIRE/SceneObject.h>
#include <FIRE/Window.h>
#include <FIRE/glmfwd.h>

namespace examples
{
InputMappingComponent::InputMappingComponent(
    FIRE::SceneObject& sceneObject,
    FIRE::InputListener& inputListener,
    FIRE::Window& window,
    FIRE::Renderer& renderer)
    : FIRE::InputComponent(inputListener)
{
    auto speed = 2.0f;
    auto& transform = sceneObject.GetTransform();
    auto moveRight = [speed, &transform] { transform.Accelerate(speed * transform.Right()); };
    auto moveLeft = [speed, &transform] { transform.Accelerate(speed * -transform.Right()); };
    auto moveUp = [speed, &transform] { transform.Accelerate(speed * transform.Up()); };
    auto moveDown = [speed, &transform] { transform.Accelerate(speed * -transform.Up()); };
    auto moveForward = [speed, &transform] { transform.Accelerate(speed * glm::normalize(transform.LookAt() - transform.Position())); };
    auto moveBackward = [speed, &transform] { transform.Accelerate(speed * glm::normalize(-(transform.LookAt() - transform.Position()))); };
    auto reset = [&transform] { transform.SetAcceleration({0.0f, 0.0f, 0.0f}); };

    inputListener.RegisterKeyEvent(FIRE::Key::KEY_D, FIRE::KeyAction::PRESS, moveRight);
    inputListener.RegisterKeyEvent(FIRE::Key::KEY_D, FIRE::KeyAction::RELEASE, reset);

    inputListener.RegisterKeyEvent(FIRE::Key::KEY_A, FIRE::KeyAction::PRESS, moveLeft);
    inputListener.RegisterKeyEvent(FIRE::Key::KEY_A, FIRE::KeyAction::RELEASE, reset);

    inputListener.RegisterKeyEvent(FIRE::Key::KEY_Q, FIRE::KeyAction::PRESS, moveUp);
    inputListener.RegisterKeyEvent(FIRE::Key::KEY_Q, FIRE::KeyAction::RELEASE, reset);

    inputListener.RegisterKeyEvent(FIRE::Key::KEY_E, FIRE::KeyAction::PRESS, moveDown);
    inputListener.RegisterKeyEvent(FIRE::Key::KEY_E, FIRE::KeyAction::RELEASE, reset);

    inputListener.RegisterKeyEvent(FIRE::Key::KEY_W, FIRE::KeyAction::PRESS, moveForward);
    inputListener.RegisterKeyEvent(FIRE::Key::KEY_W, FIRE::KeyAction::RELEASE, reset);

    inputListener.RegisterKeyEvent(FIRE::Key::KEY_S, FIRE::KeyAction::PRESS, moveBackward);
    inputListener.RegisterKeyEvent(FIRE::Key::KEY_S, FIRE::KeyAction::RELEASE, reset);

    inputListener.RegisterKeyEvent(FIRE::Key::KEY_ESC, FIRE::KeyAction::PRESS, [&window] { window.Close(); });

    inputListener.RegisterKeyEvent(FIRE::Key::KEY_R, FIRE::KeyAction::PRESS, [&renderer] { renderer.ToggleWireframe(); });

    inputListener.RegisterMouseButtonEvent(
        FIRE::MouseKey::LEFT_BUTTON, FIRE::KeyAction::PRESS, [&transform, &window, &inputListener] {
            window.CaptureCursor();

            bool firstCallback = true;
            auto rotate = [&transform, firstCallback = firstCallback](double x, double y) mutable {
                static double oldX = 0;
                static double oldY = 0;

                if(!firstCallback)
                {
                    auto const deltaX = x - oldX;
                    auto const deltaY = y - oldY;
                    transform.Rotate(transform.Up(), static_cast<float>(-deltaX) / 10.0f);    // around up-axis
                    transform.Rotate(transform.Right(), static_cast<float>(-deltaY) / 10.0f); // around right-axis
                }
                else
                {
                    firstCallback = false;
                }
                oldX = x;
                oldY = y;
            };

            inputListener.RegisterMouseEvent(rotate);
        });

    inputListener.RegisterMouseButtonEvent(
        FIRE::MouseKey::LEFT_BUTTON, FIRE::KeyAction::RELEASE, [&window, &inputListener] {
            inputListener.UnregisterMouseEvent();
            window.ReleaseCursor();
        });
}

void InputMappingComponent::DoUpdate(double, FIRE::SceneObject&, FIRE::Scene&)
{
}

std::optional<std::any> InputMappingComponent::Receive(FIRE::Message, FIRE::SceneObject&)
{
    return std::nullopt;
}
} // namespace examples
