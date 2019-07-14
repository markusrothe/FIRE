#include "GLRenderer.h"
#include "DrawAgent.h"
#include "GLShaderFactory.h"
#include "Uploader.h"
#include <FIRE/Renderable.h>
#include <FIRE/Scene.h>

namespace FIRE
{

GLRenderer::GLRenderer(
    std::unique_ptr<Uploader> uploader,
    std::unique_ptr<DrawAgent> drawAgent)
    : m_uploader(std::move(uploader))
    , m_drawAgent(std::move(drawAgent))
{
}

GLRenderer::~GLRenderer() = default;

void GLRenderer::Submit(Renderable const& renderable)
{
    m_renderables[renderable.name] = renderable;
}

void GLRenderer::Render(float, float)
{
    m_drawAgent->Clear();

    for(auto const& renderable : m_renderables)
    {
        auto buffers = m_uploader->Upload(renderable.second);
        m_drawAgent->Draw(renderable.second, buffers);
    }
}

void GLRenderer::ToggleWireframe()
{
    m_drawAgent->ToggleWireframe();
}
} // namespace FIRE
