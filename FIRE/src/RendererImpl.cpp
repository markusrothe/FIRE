#include "RendererImpl.h"
#include "DrawAgent.h"
#include "Uploader.h"
#include <cassert>

namespace FIRE
{

RendererImpl::RendererImpl(
    std::unique_ptr<Uploader> uploader, std::unique_ptr<DrawAgent> drawAgent)
    : m_uploader(std::move(uploader))
    , m_drawAgent(std::move(drawAgent))
{
}

RendererImpl::~RendererImpl() = default;

void RendererImpl::Render(Renderable const& renderable)
{
    assert(m_uploader);
    auto buffers = m_uploader->Upload(renderable);
    m_drawAgent->Draw(renderable, buffers);
}

} // namespace FIRE
