#include "RendererImpl.h"
#include "DrawAgent.h"
#include "Uploader.h"
#include <FIRE/Renderable.h>
#include <FIRE/Scene.h>
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

void RendererImpl::Render(Scene const& scene)
{
    assert(m_uploader && m_drawAgent);

    for(auto const& sceneComponent : scene.GetSceneComponents())
    {
        if(!sceneComponent)
        {
            return;
        }

        m_drawAgent->Clear();

        for(auto const& renderable : sceneComponent->GetRenderables())
        {
            if(!renderable)
            {
                continue;
            }

            auto buffers = m_uploader->Upload(*renderable);
            m_drawAgent->Draw(*renderable, buffers);
        }
    }
}

} // namespace FIRE
