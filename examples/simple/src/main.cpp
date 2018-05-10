#include "fire/windowFactory.h"
#include "fire/window.h"
#include "fire/scene.h"
#include "fire/sceneComponent.h"
#include "fire/renderer.h"
#include "fire/renderingDelegate.h"
#include "fire/binder.h"
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

    class RenderingDelegateStub : public RenderingDelegate
    {
    public:
        ~RenderingDelegateStub(){}
        virtual void Render(Renderable*) override {}
    };

    class TextureBinder : public Binder
    {
    public:
        ~TextureBinder(){}

        virtual void Bind(Renderable*) const override {}
        virtual void Unbind(Renderable*) const override {}
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

    std::unique_ptr<Fire::RenderingDelegate> renderingDelegate = std::make_unique<Fire::RenderingDelegateStub>();

    std::unique_ptr<Fire::Binder> texBinder = std::make_unique<Fire::TextureBinder>();

    // TODO: use real materialBinder class
    std::unique_ptr<Fire::Binder> materialBinder = std::make_unique<Fire::TextureBinder>();
    
    Fire::Renderer renderer(std::move(renderingDelegate), std::move(texBinder), std::move(materialBinder));

    while (!window->ShouldClose())
    {
        window->PollEvents();
        mainScene.Update();
        renderer.Render(mainScene.GetRenderables());
        window->SwapBuffers();
    }
}
