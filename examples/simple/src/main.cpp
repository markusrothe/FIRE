#include "fire/material.h"
#include "fire/materialFactory.h"
#include "fire/renderable.h"
#include "fire/renderer.h"
#include "fire/rendererFactory.h"
#include "fire/scene.h"
#include "fire/sceneComponent.h"
#include "fire/window.h"
#include "fire/windowFactory.h"
#include <memory>
#include <vector>

namespace Fire
{
class TriSceneComponent : public SceneComponent
{
public:
    TriSceneComponent()
        : m_renderable("Triangle", CreateDefaultMaterial())
    {
        auto& vertexData = m_renderable.GetVertexData();
        vertexData.AddPosition(glm::vec3(-1, 0, 0));
        vertexData.AddPosition(glm::vec3(1, 0, 0));
        vertexData.AddPosition(glm::vec3(0, 1, 0));

        auto& indexData = m_renderable.GetIndexData();
        indexData.AddIndices({0, 2, 1});

        VertexDeclaration vDecl;
        vDecl.AddSection("vertex", 3, 0, 0);
        m_renderable.SetVertexDeclaration(vDecl);
    }

    std::string GetName() const override { return "tricomp"; }

    void Update() override {}

    std::vector<Renderable*> GetRenderables() override
    {
        std::vector<Renderable*> renderables;
        renderables.push_back(&m_renderable);
        return renderables;
    }

private:
    Renderable m_renderable;
};

} // namespace Fire

int main(int, char**)
{
    auto const windowWidth = 1200u;
    auto const windowHeight = 800u;

    auto window =
        Fire::WindowFactory::CreateGLWindow("name", windowWidth, windowHeight);

    Fire::Scene mainScene("sceneName");

    auto sceneComp = std::make_unique<Fire::TriSceneComponent>();
    mainScene.AddSceneComponent(sceneComp.get());

    auto renderer = Fire::RendererFactory::CreateRenderer();

    while(!window->ShouldClose())
    {
        window->PollEvents();
        mainScene.Update();
        renderer->Render(mainScene.GetRenderables());
        window->SwapBuffers();
    }
}
