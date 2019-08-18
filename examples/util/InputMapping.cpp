#include "InputMapping.h"
#include <FIRE/Key.h>
#include <FIRE/KeyAction.h>
#include <FIRE/Message.h>
#include <FIRE/Renderer.h>
#include <FIRE/SceneObject.h>
#include <FIRE/Transform.h>
#include <FIRE/Window.h>

namespace util
{
void MapInput(FIRE::Window& window, FIRE::SceneObject& sceneObject, FIRE::Renderer& renderer)
{
    using FIRE::Key;
    using FIRE::KeyAction;
    using FIRE::KeyRegisterMessage;
    using FIRE::Message;
    using FIRE::MessageID;
    using FIRE::MouseKey;
    using FIRE::MouseKeyRegisterMessage;
    using FIRE::MouseMoveRegisterMessage;
    using FIRE::Transform;

    float const speed = 1.0f;
    auto reset = [](Transform& transform) { transform.SetAcceleration({0.0f, 0.0f, 0.0f}); };
    auto moveRight = [speed](Transform& transform) { transform.Accelerate(speed * transform.Right()); };
    auto moveLeft = [speed](Transform& transform) { transform.Accelerate(speed * -transform.Right()); };
    auto moveUp = [speed](Transform& transform) { transform.Accelerate(speed * transform.Up()); };
    auto moveDown = [speed](Transform& transform) { transform.Accelerate(speed * -transform.Up()); };
    auto moveForward = [speed](Transform& transform) { transform.Accelerate(speed * glm::normalize(transform.LookAt() - transform.Position())); };
    auto moveBackward = [speed](Transform& transform) { transform.Accelerate(speed * glm::normalize(-(transform.LookAt() - transform.Position()))); };

    sceneObject.Send(KeyRegisterMessage(MessageID::RegisterKeyEvent, Key::KEY_D, KeyAction::PRESS, moveRight));
    sceneObject.Send(KeyRegisterMessage(MessageID::RegisterKeyEvent, Key::KEY_D, KeyAction::RELEASE, reset));
    sceneObject.Send(KeyRegisterMessage(MessageID::RegisterKeyEvent, Key::KEY_A, KeyAction::PRESS, moveLeft));
    sceneObject.Send(KeyRegisterMessage(MessageID::RegisterKeyEvent, Key::KEY_A, KeyAction::RELEASE, reset));
    sceneObject.Send(KeyRegisterMessage(MessageID::RegisterKeyEvent, Key::KEY_Q, KeyAction::PRESS, moveUp));
    sceneObject.Send(KeyRegisterMessage(MessageID::RegisterKeyEvent, Key::KEY_Q, KeyAction::RELEASE, reset));
    sceneObject.Send(KeyRegisterMessage(MessageID::RegisterKeyEvent, Key::KEY_E, KeyAction::PRESS, moveDown));
    sceneObject.Send(KeyRegisterMessage(MessageID::RegisterKeyEvent, Key::KEY_E, KeyAction::RELEASE, reset));
    sceneObject.Send(KeyRegisterMessage(MessageID::RegisterKeyEvent, Key::KEY_W, KeyAction::PRESS, moveForward));
    sceneObject.Send(KeyRegisterMessage(MessageID::RegisterKeyEvent, Key::KEY_W, KeyAction::RELEASE, reset));
    sceneObject.Send(KeyRegisterMessage(MessageID::RegisterKeyEvent, Key::KEY_S, KeyAction::PRESS, moveBackward));
    sceneObject.Send(KeyRegisterMessage(MessageID::RegisterKeyEvent, Key::KEY_S, KeyAction::RELEASE, reset));
    sceneObject.Send(KeyRegisterMessage(MessageID::RegisterKeyEvent, Key::KEY_ESC, KeyAction::PRESS, [&window](Transform&) { window.Close(); }));
    sceneObject.Send(KeyRegisterMessage(MessageID::RegisterKeyEvent, Key::KEY_R, KeyAction::PRESS, [&renderer](Transform&) { renderer.ToggleWireframe(); }));

    sceneObject.Send(MouseKeyRegisterMessage(
        MessageID::RegisterMouseButtonEvent,
        MouseKey::LEFT_BUTTON, KeyAction::PRESS, [&window, &sceneObject](Transform& transform) {
            window.CaptureCursor();

            bool firstCallback = true;
            auto rotate = [firstCallback = firstCallback, &transform](double x, double y) mutable {
                static double oldX = 0;
                static double oldY = 0;

                if(!firstCallback)
                {
                    auto const deltaX = x - oldX;
                    auto const deltaY = y - oldY;
                    transform.Rotate(transform.Up(), static_cast<float>(-deltaX) / 10.0f);    // around up-axis
                    transform.Rotate(transform.Right(), static_cast<float>(-deltaY) / 10.0f); // around right-axis
                }
                firstCallback = false;
                oldX = x;
                oldY = y;
            };

            sceneObject.Send(MouseMoveRegisterMessage(MessageID::RegisterMouseMoveEvent, rotate));
        }));

    sceneObject.Send(MouseKeyRegisterMessage(
        MessageID::RegisterMouseButtonEvent,
        MouseKey::LEFT_BUTTON, KeyAction::RELEASE, [&sceneObject, &window](Transform&) {
            sceneObject.Send(Message(MessageID::UnregisterMouseMoveEvent));
            window.ReleaseCursor();
        }));
}
} // namespace util