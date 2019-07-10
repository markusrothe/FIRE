#include "RendererImpl.h"
#include "DrawAgent.h"
#include "GLShaderFactory.h"
#include "Uploader.h"
#include <FIRE/Renderable.h>
#include <FIRE/Scene.h>

namespace FIRE
{

RendererImpl::RendererImpl(
    std::unique_ptr<Uploader> uploader,
    std::unique_ptr<DrawAgent> drawAgent)
    : m_uploader(std::move(uploader))
    , m_drawAgent(std::move(drawAgent))
{
}

RendererImpl::~RendererImpl() = default;

void RendererImpl::Submit(Renderable const& renderable)
{
    m_renderables.push_back(renderable);
}

void RendererImpl::Render(float, float)
{
    m_drawAgent->Clear();

    for(auto const& renderable : m_renderables)
    {
        auto buffers = m_uploader->Upload(renderable);
        m_drawAgent->Draw(renderable, buffers);
    }

    m_renderables.clear();
}
} // namespace FIRE
