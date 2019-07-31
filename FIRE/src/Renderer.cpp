#include "FIRE/Renderer.h"
#include "Draw.h"
#include "MaterialBinder.h"
#include "MeshUploader.h"
#include "VertexLayout.h"
#include "VertexLayoutBinder.h"
#include <FIRE/Renderable.h>
#include <FIRE/TextOverlay.h>

namespace FIRE
{

Renderer::Renderer(
    std::unique_ptr<Draw> draw,
    std::unique_ptr<VertexLayoutBinder> vertexLayoutBinder,
    std::unique_ptr<MaterialBinder> materialBinder,
    std::unique_ptr<MeshUploader> meshUploader)
    : m_draw(std::move(draw))
    , m_vertexLayoutBinder(std::move(vertexLayoutBinder))
    , m_materialBinder(std::move(materialBinder))
    , m_meshUploader(std::move(meshUploader))
{
}

Renderer::~Renderer() = default;

void Renderer::Submit(Renderable const& renderable)
{
    m_renderables[renderable.name] = renderable;
}

void Renderer::Submit(TextOverlay const& overlay)
{
    m_overlays[overlay.id] = overlay;
}

void Renderer::Render(float, float)
{
    m_draw->Clear();

    for(auto const& renderable : m_renderables)
    {
        Render(renderable.second);
    }

    //    for(auto const& overlay : m_overlays)
    //    {
    //        m_textOverlayRenderer->Render(overlay.second, windowWidth, windowHeight);
    //    }
}

void Renderer::Render(Renderable const& renderable)
{
    auto const vertexLayout = m_meshUploader->Upload(*renderable.mesh, renderable.material.ShaderId());
    m_vertexLayoutBinder->Bind(vertexLayout);
    m_vertexLayoutBinder->BindIndexBuffer();
    m_materialBinder->Bind(renderable.material);
    m_draw->DoDraw(renderable.mesh);
    m_materialBinder->Release();
    m_vertexLayoutBinder->Release();
}

void Renderer::ToggleWireframe()
{
    m_draw->ToggleWireframe();
}
} // namespace FIRE
