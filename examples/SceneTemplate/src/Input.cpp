#include <SceneTemplate/Input.h>

#include <FIRE/Camera.h>
#include <FIRE/InputListener.h>
#include <FIRE/Window.h>

namespace SceneTemplate
{
void MapInput(FIRE::Camera& cam, FIRE::Window& window)
{
    auto input{std::make_shared<FIRE::InputListener>()};
    window.SetInputListener(input);

    auto moveRight = [&cam] { auto& camTransform = cam.GetTransform(); camTransform.Translate(camTransform.Right()); };
    input->RegisterKeyEvent(FIRE::Key::KEY_D, FIRE::KeyAction::PRESS, moveRight);
    input->RegisterKeyEvent(FIRE::Key::KEY_D, FIRE::KeyAction::REPEAT, moveRight);

    auto moveLeft = [&cam] { auto& camTransform = cam.GetTransform(); camTransform.Translate(-camTransform.Right()); };
    input->RegisterKeyEvent(FIRE::Key::KEY_A, FIRE::KeyAction::PRESS, moveLeft);
    input->RegisterKeyEvent(FIRE::Key::KEY_A, FIRE::KeyAction::REPEAT, moveLeft);

    auto moveUp = [&cam] { auto& camTransform = cam.GetTransform(); camTransform.Translate(camTransform.Up()); };
    input->RegisterKeyEvent(FIRE::Key::KEY_Q, FIRE::KeyAction::PRESS, moveUp);
    input->RegisterKeyEvent(FIRE::Key::KEY_Q, FIRE::KeyAction::REPEAT, moveUp);

    auto moveDown = [&cam] { auto& camTransform = cam.GetTransform(); camTransform.Translate(-camTransform.Up()); };
    input->RegisterKeyEvent(FIRE::Key::KEY_E, FIRE::KeyAction::PRESS, moveDown);
    input->RegisterKeyEvent(FIRE::Key::KEY_E, FIRE::KeyAction::REPEAT, moveDown);

    auto moveForward = [&cam] { auto& camTransform = cam.GetTransform(); camTransform.Translate(camTransform.LookAt() - camTransform.Position()); };
    input->RegisterKeyEvent(FIRE::Key::KEY_W, FIRE::KeyAction::PRESS, moveForward);
    input->RegisterKeyEvent(FIRE::Key::KEY_W, FIRE::KeyAction::REPEAT, moveForward);

    auto moveBackward = [&cam] { auto& camTransform = cam.GetTransform(); camTransform.Translate(-(camTransform.LookAt() - camTransform.Position())); };
    input->RegisterKeyEvent(FIRE::Key::KEY_S, FIRE::KeyAction::PRESS, moveBackward);
    input->RegisterKeyEvent(FIRE::Key::KEY_S, FIRE::KeyAction::REPEAT, moveBackward);

    auto closeWindow = [&window] { window.Close(); };
    input->RegisterKeyEvent(FIRE::Key::KEY_ESC, FIRE::KeyAction::PRESS, closeWindow);

    input->RegisterMouseButtonEvent(
        FIRE::MouseKey::LEFT_BUTTON, FIRE::KeyAction::PRESS, [&cam, input, &window] {
            window.CaptureCursor();

            bool firstCallback = true;
            auto rotate = [&cam, firstCallback = std::move(firstCallback)](double x, double y) mutable {
                static double oldX = 0;
                static double oldY = 0;

                if(!firstCallback)
                {
                    auto const deltaX = x - oldX;
                    auto const deltaY = y - oldY;
                    auto& camTransform = cam.GetTransform();
                    camTransform.Rotate(camTransform.Up(), static_cast<float>(-deltaX) / 10.0f);    // around up-axis
                    camTransform.Rotate(camTransform.Right(), static_cast<float>(-deltaY) / 10.0f); // around right-axis
                }
                else
                {
                    firstCallback = false;
                }
                oldX = x;
                oldY = y;
            };

            input->RegisterMouseEvent(rotate);
        });

    input->RegisterMouseButtonEvent(
        FIRE::MouseKey::LEFT_BUTTON, FIRE::KeyAction::RELEASE, [input, &window] {
            input->UnregisterMouseEvent();
            window.ReleaseCursor();
        });
}
} // namespace SceneTemplate
