#include "rendererFactory.h"
#include "renderingDelegate.h"
#include "textureBinder.h"

#include <utility>

namespace
{

    class RenderingDelegateStub : public Fire::RenderingDelegate
    {
    public:
        ~RenderingDelegateStub(){}
        virtual void Render(Fire::Renderable*) override {}
    };
    
} // namespace

namespace Fire
{
    namespace RendererFactory
    {
        std::unique_ptr<Renderer> CreateRenderer()
        {
            std::unique_ptr<Fire::RenderingDelegate> renderingDelegate = std::make_unique<RenderingDelegateStub>();

            std::unique_ptr<Fire::Binder> texBinder = std::make_unique<TextureBinder>();
        
            std::unique_ptr<Fire::Binder> materialBinder = std::make_unique<TextureBinder>();
        
            return std::make_unique<Renderer>(std::move(renderingDelegate), std::move(texBinder), std::move(materialBinder));
        }
    } // namespace RendererFactory
    
} // namespace Fire
