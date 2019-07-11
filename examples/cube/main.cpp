
#include "CubeCameraComponent.h"
#include "CubeInputComponent.h"
#include "CubeLightComponent.h"
#include "CubeOverlayComponent.h"
#include "CubeRenderingComponent.h"

#include <FIRE/GLFactory.h>
#include <FIRE/InputListener.h>
#include <FIRE/MaterialFactory.h>
#include <FIRE/MeshManager.h>
#include <FIRE/RenderContext.h>
#include <FIRE/Renderer.h>
#include <FIRE/Scene.h>
#include <FIRE/SceneObject.h>
#include <FIRE/TextRenderer.h>
#include <FIRE/Window.h>
#include <chrono>

#include <memory>
#include <thread>
using namespace std::chrono_literals;
namespace
{
unsigned int constexpr WINDOW_WIDTH = 800;
unsigned int constexpr WINDOW_HEIGHT = 600;
} // namespace

int main(int, char**)
{
    FIRE::Window window = FIRE::GLFactory::InitWindow("FIRE - cube", WINDOW_WIDTH, WINDOW_HEIGHT);
    auto input{std::make_shared<FIRE::InputListener>()};
    window.SetInputListener(input);

    FIRE::MeshManager meshManager;
    FIRE::MaterialFactory materialFactory(FIRE::GLFactory::CreateShaderFactory());
    auto renderer{FIRE::GLFactory::CreateRenderer(meshManager)};
    auto textRenderer{FIRE::GLFactory::CreateTextRenderer()};

    FIRE::Scene scene;
    auto& cubeObject = scene.CreateSceneObject("cube");
    cubeObject.AddComponent(
        std::make_unique<examples::CubeRenderingComponent>(
            *renderer, meshManager, materialFactory));

    auto& mainCamera = scene.CreateSceneObject("cam");
    mainCamera.AddComponent(
        std::make_unique<examples::CubeInputComponent>(mainCamera, *input, window));
    mainCamera.AddComponent(
        std::make_unique<examples::CubeCameraComponent>(
            mainCamera, 70.0f, static_cast<float>(window.GetWidth()) / static_cast<float>(window.GetHeight()), 0.01f, 500.0f));

    auto& sceneLight = scene.CreateSceneObject("light");
    sceneLight.AddComponent(
        std::make_unique<examples::CubeLightComponent>());

    auto& overlay = scene.CreateSceneObject("overlay");
    overlay.AddComponent(
        std::make_unique<examples::CubeOverlayComponent>(*textRenderer));

    auto lastTime = std::chrono::high_resolution_clock::now();
    std::chrono::nanoseconds lag{0ns};
    std::chrono::nanoseconds timestep{16ms};
    while(!window.ShouldClose())
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto deltaTime = currentTime - lastTime;

        lastTime = currentTime;
        lag += deltaTime;
        window.PollEvents();

        while(lag >= timestep)
        {
            scene.Update(std::chrono::duration<double>(lag).count());
            lag -= timestep;
        }

        renderer->Render(WINDOW_WIDTH, WINDOW_HEIGHT);
        textRenderer->Render(WINDOW_WIDTH, WINDOW_HEIGHT);
        window.SwapBuffers();
    }
}
