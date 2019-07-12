#include "CubeInputComponent.h"
#include <FIRE/InputListener.h>
#include <FIRE/Message.h>
#include <FIRE/Scene.h>
#include <FIRE/SceneObject.h>
#include <FIRE/Window.h>

namespace examples
{
CubeInputComponent::CubeInputComponent(FIRE::SceneObject& sceneObject, FIRE::InputListener& inputListener, FIRE::Window& window)
    : FIRE::InputComponent(inputListener)
{
    auto& transform = sceneObject.GetTransform();
    auto moveRight = [&transform] { transform.Accelerate(transform.Right()); };
    auto moveLeft = [&transform] { transform.Accelerate(-transform.Right()); };
    auto moveUp = [&transform] { transform.Accelerate(transform.Up()); };
    auto moveDown = [&transform] { transform.Accelerate(-transform.Up()); };
    auto moveForward = [&transform] { transform.Accelerate(glm::normalize(transform.LookAt() - transform.Position())); };
    auto moveBackward = [&transform] { transform.Accelerate(glm::normalize(-(transform.LookAt() - transform.Position()))); };
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

    auto closeWindow = [&window, &inputListener] { window.Close(); };
    inputListener.RegisterKeyEvent(FIRE::Key::KEY_ESC, FIRE::KeyAction::PRESS, closeWindow);

    inputListener.RegisterMouseButtonEvent(
        FIRE::MouseKey::LEFT_BUTTON, FIRE::KeyAction::PRESS, [&transform, &window, &inputListener] {
            window.CaptureCursor();

            bool firstCallback = true;
            auto rotate = [&transform, firstCallback = std::move(firstCallback)](double x, double y) mutable {
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

void CubeInputComponent::DoUpdate(double, FIRE::SceneObject&, FIRE::Scene&)
{
}

std::optional<std::any> CubeInputComponent::Receive(FIRE::Message)
{
    return std::nullopt;
}
} // namespace examples
