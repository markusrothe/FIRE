#include "FPSOverlayComponent.h"
#include <FIRE/AssetFacade.h>
#include <FIRE/GLFactory.h>
#include <FIRE/InputListener.h>
#include <FIRE/MainLoop.h>
#include <FIRE/Message.h>
#include <FIRE/RenderContext.h>
#include <FIRE/Renderer.h>
#include <FIRE/Scene.h>
#include <FIRE/Window.h>

#include <FIRE/CameraComponent.h>
#include <FIRE/InputComponent.h>
#include <FIRE/LightComponent.h>
#include <FIRE/RenderingComponent.h>
#include <memory>

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

    float constexpr speed = 0.4f;
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

int main(int, char**)
{
    auto window{FIRE::GLFactory::CreateWindow("FIRE - cube", 800, 600)};
    auto assets{FIRE::GLFactory::CreateAssetFacade()};
    auto renderer{FIRE::GLFactory::CreateRenderer(assets)};

    FIRE::Scene scene;
    assets->SubmitShadersFromFiles(
        "phong",
        {{FIRE::ShaderType::VERTEX_SHADER, "PhongVS.glsl"}, {FIRE::ShaderType::FRAGMENT_SHADER, "PhongFS.glsl"}});

    auto cubeRenderables = assets->CreateRenderables("cube", 1u)
                               .WithMesh("cubeMesh", FIRE::MeshCategory::Cube)
                               .WithMaterial("phong")
                               .Build();

    auto& cubeObject = scene.CreateSceneObject("cube");
    cubeObject.AddComponent(std::make_unique<FIRE::RenderingComponent>(*renderer, std::move(cubeRenderables)));
    cubeObject.GetTransform().SetPosition({0.0f, 4.0f, 0.0f});
    cubeObject.GetTransform().Scale({10.0f, 10.0f, 10.0f});

    auto& mainCamera = scene.CreateSceneObject("cam");
    mainCamera.AddComponent(std::make_unique<FIRE::InputComponent>(window));
    MapInput(window, mainCamera, *renderer);
    mainCamera.AddComponent(std::make_unique<FIRE::CameraComponent>(
        70.0f, static_cast<float>(window.GetWidth()) / static_cast<float>(window.GetHeight()), 0.1f, 3000.0f));
    mainCamera.GetTransform().SetPosition({20.0f, 20.0f, 20.0f});
    mainCamera.GetTransform().SetLookAt({0.0f, 0.0f, 0.0f});

    auto& sceneLight = scene.CreateSceneObject("light");
    sceneLight.AddComponent(std::make_unique<FIRE::LightComponent>());
    sceneLight.GetTransform().SetPosition({0.0f, 100.0f, 0.0f});

    //auto& overlay = scene.CreateSceneObject("overlay");
    //overlay.AddComponent(std::make_unique<examples::FPSOverlayComponent>(renderer, assets));

    FIRE::MainLoop(window, scene, *renderer);
}
