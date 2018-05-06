#include "fire/windowFactory.h"
#include "fire/window.h"
#include "fire/scene.h"
#include "fire/sceneComponent.h"
#include "fire/renderer.h"
#include <memory>
#include <vector>

namespace Fire
{
    class QuadSceneComponent : public SceneComponent
    {
    public:
        std::string GetName() const override { return "quadcomp"; }

        void Update() override {}

        std::vector<Renderable*> GetRenderables() const override
        {
            return std::vector<Renderable*>();
        }
    };
} // namespace Fire

int main(int, char**)
{
    auto const windowWidth = 1200u;
    auto const windowHeight = 800u;

    auto window = Fire::WindowFactory::CreateGLWindow("name", windowWidth, windowHeight);

    Fire::Scene mainScene("sceneName");

    auto sceneComp = std::make_unique<Fire::QuadSceneComponent>();
    mainScene.AddSceneComponent(sceneComp.get());
  
    Fire::Renderer renderer;

    while (!window->ShouldClose())
    {
        window->PollEvents();
        mainScene.Update();
        renderer.Render(mainScene.GetRenderables());
        window->SwapBuffers();
    }
}
