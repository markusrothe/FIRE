#include "RendererImpl.h"
#include "DrawAgent.h"
#include "GLShaderFactory.h"
#include "GLTextRenderer.h"
#include "Uploader.h"
#include <FIRE/Renderable.h>
#include <FIRE/Scene.h>
#include <FIRE/TextOverlay.h>

namespace FIRE
{

RendererImpl::RendererImpl(
    std::unique_ptr<Uploader> uploader,
    std::unique_ptr<DrawAgent> drawAgent,
    std::unique_ptr<TextRenderer> textRenderer)
    : m_uploader(std::move(uploader))
    , m_drawAgent(std::move(drawAgent))
    , m_textRenderer(std::move(textRenderer))
{
}

RendererImpl::~RendererImpl() = default;

void RendererImpl::Render(Scene const& scene, float windowWidth, float windowHeight)
{
    m_drawAgent->Clear();

    for(auto const& renderable : scene.CollectRenderables())
    {
        auto buffers = m_uploader->Upload(renderable);
        m_drawAgent->Draw(renderable, buffers);
    }

    for(auto const& textOverlay : scene.CollectTextOverlays())
    {
        m_textRenderer->Render(textOverlay, windowWidth, windowHeight);
    }
}
} // namespace FIRE
