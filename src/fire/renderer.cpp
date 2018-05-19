#include "renderer.h"
#include "renderingDelegate.h"
#include "renderable.h"
#include "binder.h"

namespace Fire
{
    Renderer::Renderer(std::unique_ptr<RenderingDelegate>&& renderingDelegate,
                       std::unique_ptr<Binder>&& textureBinder,
                       std::unique_ptr<Binder>&& materialBinder)
        : m_renderingDelegate(std::move(renderingDelegate))
        , m_textureBinder(std::move(textureBinder))
        , m_materialBinder(std::move(materialBinder))
    {        
    }

    Renderer::~Renderer()
    {
        
    }

    void Renderer::Render(std::vector<Renderable*> const& renderables)
    {
        for(auto renderable : renderables)
        {
            m_textureBinder->Bind(renderable);
            m_materialBinder->Bind(renderable);           
            
            m_renderingDelegate->Render(renderable);
            
            m_materialBinder->Unbind(renderable);
            m_textureBinder->Unbind(renderable);
        }
    }
} // namespace Fire
