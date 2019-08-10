#include "FIRE/Renderer.h"
#include "Draw.h"
#include "FIRE/FontCharacter.h"
#include "MaterialBinder.h"
#include "VertexLayoutFactory.h"
#include <FIRE/AssetFacade.h>
#include <FIRE/Renderable.h>
#include <FIRE/TextOverlay.h>
#include <array>
namespace FIRE
{
namespace
{
//TODO: Create in MeshFactory?!
std::array<float, 24> GetFontCharQuad(FontCharacter const& ch, float x, float y, float scale)
{
    float xpos = x + ch.bearing.x * scale;
    float ypos = y - static_cast<float>((ch.size.y - ch.bearing.y)) * scale;

    float w = (float)ch.size.x * scale;
    float h = (float)ch.size.y * scale;
    return {
        xpos, ypos + h, 0.0, 0.0,
        xpos, ypos, 0.0, 1.0,
        xpos + w, ypos, 1.0, 1.0,

        xpos, ypos + h, 0.0, 0.0,
        xpos + w, ypos, 1.0, 1.0,
        xpos + w, ypos + h, 1.0, 0.0};
}
} // namespace
Renderer::Renderer(
    std::unique_ptr<Draw> draw,
    std::unique_ptr<MaterialBinder> materialBinder,
    std::unique_ptr<VertexLayoutFactory> vertexLayoutFactory,
    std::shared_ptr<AssetFacade> assets)
    : m_draw(std::move(draw))
    , m_materialBinder(std::move(materialBinder))
    , m_vertexLayoutFactory(std::move(vertexLayoutFactory))
    , m_assets(std::move(assets))
{
}

Renderer::~Renderer() = default;

void Renderer::Submit(Renderable const& renderable)
{
    m_renderables[renderable.name] = renderable;
}

void Renderer::Submit(TextOverlay const& overlay)
{
    m_overlays[overlay.name] = overlay;
}

void Renderer::Render(float windowWidth, float windowHeight)
{
    m_draw->Clear();

    for(auto const& renderable : m_renderables)
    {
        Render(renderable.second);
    }

    for(auto const& overlay : m_overlays)
    {
        Render(overlay.second, windowWidth, windowHeight);
    }
}

void Renderer::Render(Renderable renderable)
{
    auto& vertexLayout = m_vertexLayoutFactory->CreateStaticIndexedLayout(renderable);
    m_materialBinder->Bind(renderable.material);
    m_draw->DoDrawIndexed(vertexLayout, renderable.mesh->GetMeshType().primitives, static_cast<uint32_t>(renderable.mesh->Indices().size()));
    m_materialBinder->Release();
}

void Renderer::Render(TextOverlay overlay, float width, float height)
{
    auto& vertexLayout = m_vertexLayoutFactory->CreateDynamicLayout(overlay);
    m_materialBinder->Bind(overlay.material);

    float x = overlay.x * width;
    float y = overlay.y * height;
    for(auto const& c : overlay.text)
    {
        FontCharacter ch = m_assets->CreateFontCharacter(c);
        if(ch.texture)
        {
            ch.texture->Bind(0);
        }
        auto vertices = GetFontCharQuad(ch, x, y, overlay.scale);
        vertexLayout.BufferSubData(0u, sizeof(vertices), vertices.data());
        m_draw->DoDraw(vertexLayout, MeshPrimitives::Triangles, 6u);

        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.advance >> 6) * overlay.scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
    }

    m_materialBinder->Release();
}

void Renderer::ToggleWireframe()
{
    m_draw->ToggleWireframe();
}
} // namespace FIRE
