
#include "GLDrawAgent.h"
#include "GLRenderContext.h"
#include "GLShaderFactory.h"
#include "GLUploader.h"
#include "RendererImpl.h"
#include <FIRE/GLFactory.h>
#include <FIRE/Window.h>

namespace FIRE
{
namespace GLFactory
{
Window InitWindow(std::string title, uint32_t width, uint32_t height)
{
    Window window(std::move(title), width, height);
    window.SetRenderContext(CreateRenderContext(window));
    return window; //will move as copies are disabled.
}

std::unique_ptr<RenderContext> CreateRenderContext(Window& window)
{
    return std::make_unique<GLRenderContext>(window);
}

std::unique_ptr<Renderer> CreateRenderer(MeshManager& meshManager)
{
    return std::make_unique<RendererImpl>(
        std::make_unique<GLUploader>(meshManager),
        std::make_unique<GLDrawAgent>(meshManager));
}

std::unique_ptr<ShaderFactory> CreateShaderFactory()
{
    return std::make_unique<GLShaderFactory>();
}
} // namespace GLFactory
} // namespace FIRE
