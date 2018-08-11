#include "renderer.h"
#include "binder.h"
#include "material.h"
#include "renderable.h"
#include "renderingDelegate.h"
namespace Fire
{

Renderer::Renderer(std::unique_ptr<RenderingDelegate> renderingDelegate)
    : m_renderingDelegate(std::move(renderingDelegate))
{
}

Renderer::~Renderer() = default;

void Renderer::Render(std::vector<Renderable*> const& renderables)
{
    for(auto renderable : renderables)
    {
        if(renderable)
        {
            m_renderingDelegate->Bind(renderable);

            auto material = renderable->GetMaterial();

            if(material)
            {
                material->Bind();
            }

            m_renderingDelegate->Render(renderable);

            if(material)
            {
                material->Unbind();
            }

            m_renderingDelegate->Unbind(renderable);
        }
    }
}
} // namespace Fire
