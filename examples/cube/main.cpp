
#include "CubeCameraComponent.h"
#include "CubeRenderingComponent.h"

#include <FIRE/GLFactory.h>
#include <FIRE/MaterialFactory.h>
#include <FIRE/MeshManager.h>
#include <FIRE/RenderContext.h>
#include <FIRE/Renderer.h>
#include <FIRE/Scene.h>
#include <FIRE/SceneObject.h>
#include <FIRE/Window.h>
//#include <SceneTemplate/SceneTemplate.h>
#include <memory>

namespace
{
unsigned int constexpr WINDOW_WIDTH = 800;
unsigned int constexpr WINDOW_HEIGHT = 600;
} // namespace

int main(int, char**)
{
    FIRE::Window window = FIRE::GLFactory::InitWindow("FIRE - cube", WINDOW_WIDTH, WINDOW_HEIGHT);
    FIRE::MeshManager meshManager;
    FIRE::MaterialFactory materialFactory(FIRE::GLFactory::CreateShaderFactory());
    auto renderer{FIRE::GLFactory::CreateRenderer(meshManager)};

    FIRE::Scene scene;
    auto& cubeObject = scene.CreateSceneObject("cube");
    cubeObject.SetRenderingComponent(
        std::make_unique<examples::CubeRenderingComponent>(
            *renderer, meshManager, materialFactory));

    auto& mainCamera = scene.CreateSceneObject("cam");
    mainCamera.SetCameraComponent(
        std::make_unique<examples::CubeCameraComponent>(
            70.0f, static_cast<float>(window.GetWidth()) / static_cast<float>(window.GetHeight()), 0.01f, 500.0f));

    while(!window.ShouldClose())
    {
        window.PollEvents();
        scene.Update();
        renderer->Render(WINDOW_WIDTH, WINDOW_HEIGHT);
        window.SwapBuffers();
    }
}
