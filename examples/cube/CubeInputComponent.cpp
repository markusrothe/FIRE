#include "CubeInputComponent.h"
#include <FIRE/InputListener.h>
#include <FIRE/Message.h>
#include <FIRE/Scene.h>
#include <FIRE/SceneObject.h>
#include <FIRE/Window.h>

namespace examples
{
CubeInputComponent::CubeInputComponent(FIRE::InputListener& inputListener, FIRE::Window& window)
    : FIRE::InputComponent(inputListener)
    , window(window)
{
}

void CubeInputComponent::Init(FIRE::SceneObject& sceneObject)
{
    auto& transform = sceneObject.GetTransform();
    auto moveRight = [&transform] { transform.Translate(transform.Right()); };
    inputListener.RegisterKeyEvent(FIRE::Key::KEY_D, FIRE::KeyAction::PRESS, moveRight);
    inputListener.RegisterKeyEvent(FIRE::Key::KEY_D, FIRE::KeyAction::REPEAT, moveRight);

    auto moveLeft = [&transform] { transform.Translate(-transform.Right()); };
    inputListener.RegisterKeyEvent(FIRE::Key::KEY_A, FIRE::KeyAction::PRESS, moveLeft);
    inputListener.RegisterKeyEvent(FIRE::Key::KEY_A, FIRE::KeyAction::REPEAT, moveLeft);

    auto moveUp = [&transform] { transform.Translate(transform.Up()); };
    inputListener.RegisterKeyEvent(FIRE::Key::KEY_Q, FIRE::KeyAction::PRESS, moveUp);
    inputListener.RegisterKeyEvent(FIRE::Key::KEY_Q, FIRE::KeyAction::REPEAT, moveUp);

    auto moveDown = [&transform] { transform.Translate(-transform.Up()); };
    inputListener.RegisterKeyEvent(FIRE::Key::KEY_E, FIRE::KeyAction::PRESS, moveDown);
    inputListener.RegisterKeyEvent(FIRE::Key::KEY_E, FIRE::KeyAction::REPEAT, moveDown);

    auto moveForward = [&transform] { transform.Translate(transform.LookAt() - transform.Position()); };
    inputListener.RegisterKeyEvent(FIRE::Key::KEY_W, FIRE::KeyAction::PRESS, moveForward);
    inputListener.RegisterKeyEvent(FIRE::Key::KEY_W, FIRE::KeyAction::REPEAT, moveForward);

    auto moveBackward = [&transform] { transform.Translate(-(transform.LookAt() - transform.Position())); };
    inputListener.RegisterKeyEvent(FIRE::Key::KEY_S, FIRE::KeyAction::PRESS, moveBackward);
    inputListener.RegisterKeyEvent(FIRE::Key::KEY_S, FIRE::KeyAction::REPEAT, moveBackward);

    auto closeWindow = [this] { window.Close(); };
    inputListener.RegisterKeyEvent(FIRE::Key::KEY_ESC, FIRE::KeyAction::PRESS, closeWindow);

    inputListener.RegisterMouseButtonEvent(
        FIRE::MouseKey::LEFT_BUTTON, FIRE::KeyAction::PRESS, [&transform, this] {
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
        FIRE::MouseKey::LEFT_BUTTON, FIRE::KeyAction::RELEASE, [this] {
            inputListener.UnregisterMouseEvent();
            window.ReleaseCursor();
        });
}

void CubeInputComponent::DoUpdate(FIRE::SceneObject& sceneObject, FIRE::Scene&)
{
    static bool initialized = false;

    if(!initialized)
    {
        Init(sceneObject);
        initialized = true;
    }
}

std::optional<std::any> CubeInputComponent::Receive(FIRE::Message)
{
    return std::nullopt;
}
} // namespace examples
