
#include <FIRE/Camera.h>
#include <FIRE/GLFactory.h>
#include <FIRE/MeshFactory.h>
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
    FIRE::Window window{"FIRE cube example", WINDOW_WIDTH, WINDOW_HEIGHT};
    auto context{FIRE::GLFactory::CreateRenderContext(window)};
    window.SetRenderContext(std::move(context));

    FIRE::MeshFactory factory;
    FIRE::Scene scene(FIRE::Camera("cam", {0.0f, 2.0f, 10.0f}, {0.0f, 2.0f, 0.0f}));
    FIRE::Camera& cam = scene.GetCamera();
    scene.AddSceneComponent(std::make_shared<SceneTemplate::SceneTemplate>(cam, window, factory));

    auto renderer{FIRE::GLFactory::CreateRenderer(factory)};
    while(!window.ShouldClose())
    {
        window.PollEvents();

        scene.Update();

        renderer->Render(scene);
        window.SwapBuffers();
    }
}
