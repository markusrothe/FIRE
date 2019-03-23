
#include "GLDrawAgent.h"
#include "GLRenderContext.h"
#include "GLUploader.h"
#include "MaterialManager.h"
#include "RendererImpl.h"
#include <FIRE/GLFactory.h>
#include <FIRE/Window.h>

namespace FIRE
{
namespace GLFactory
{

std::unique_ptr<RenderContext> CreateRenderContext(Window& window)
{
    return std::make_unique<GLRenderContext>(window);
}

std::unique_ptr<Renderer> CreateRenderer()
{
    auto materialManager = std::make_shared<MaterialManager>();

    return std::make_unique<RendererImpl>(
        std::make_unique<GLUploader>(materialManager),
        std::make_unique<GLDrawAgent>());
}
} // namespace GLFactory
} // namespace FIRE
