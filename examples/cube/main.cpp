#include "CubeSceneComponent.h"
#include <FIRE/Camera.h>
#include <FIRE/GLFactory.h>
#include <FIRE/MaterialFactory.h>
#include <FIRE/MeshManager.h>
#include <FIRE/RenderContext.h>
#include <FIRE/Renderer.h>
#include <FIRE/Scene.h>
#include <FIRE/Window.h>
#include <SceneTemplate/SceneTemplate.h>
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

    FIRE::Scene scene(FIRE::Camera("cam", {0.0f, 2.0f, 10.0f}, {0.0f, 2.0f, 0.0f}));
    FIRE::Camera& cam = scene.GetCamera();
    scene.AddSceneComponent(std::make_shared<SceneTemplate::SceneTemplate>(cam, window, meshManager, materialFactory));
    scene.AddSceneComponent(std::make_shared<examples::CubeSceneComponent>(window, meshManager, materialFactory));

    auto renderer{FIRE::GLFactory::CreateRenderer(meshManager)};
    while(!window.ShouldClose())
    {
        window.PollEvents();
        scene.Update();
        renderer->Render(scene, WINDOW_WIDTH, WINDOW_HEIGHT);
        window.SwapBuffers();
    }
}
