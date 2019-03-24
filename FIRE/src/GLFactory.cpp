
#include "GLDrawAgent.h"
#include "GLRenderContext.h"
#include "GLShaderFactory.h"
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
    auto shaderFactory = std::make_unique<GLShaderFactory>();
    auto materialManager = std::make_shared<MaterialManager>(std::move(shaderFactory));

    return std::make_unique<RendererImpl>(
        std::make_unique<GLUploader>(materialManager),
        std::make_unique<GLDrawAgent>());
}
} // namespace GLFactory
} // namespace FIRE
