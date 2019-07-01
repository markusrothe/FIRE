#include "CubeSceneComponent.h"
#include <FIRE/Camera.h>
#include <FIRE/GLFactory.h>
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
    FIRE::Scene scene(FIRE::Camera("cam", {0.0f, 2.0f, 10.0f}, {0.0f, 2.0f, 0.0f}));
    FIRE::Camera& cam = scene.GetCamera();
    scene.AddSceneComponent(std::make_shared<SceneTemplate::SceneTemplate>(cam, window, meshManager));
    scene.AddSceneComponent(std::make_shared<examples::CubeSceneComponent>(window, meshManager));
    auto renderer{FIRE::GLFactory::CreateRenderer(meshManager)};
    while(!window.ShouldClose())
    {
        window.PollEvents();

        scene.Update();
        renderer->Render(scene);
        window.SwapBuffers();
    }
}
