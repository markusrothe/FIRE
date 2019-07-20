
#include "GLShaderFactory.h"

#include "GLDrawAgent.h"
#include "GLFontTextureFactory.h"
#include "GLRenderContext.h"
#include "GLTextRenderer.h"
#include "GLUploader.h"
#include "GLRenderer.h"
#include "TextureFactory.h"
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
    return std::make_unique<GLRenderer>(
        std::make_unique<GLUploader>(meshManager),
        std::make_unique<GLDrawAgent>(meshManager));
}

std::unique_ptr<TextRenderer> CreateTextRenderer()
{
    auto fontTexFactory = std::make_unique<GLFontTextureFactory>();
    auto texFactory = std::make_unique<TextureFactory>(std::move(fontTexFactory));
    return std::make_unique<GLTextRenderer>(std::move(texFactory));
}

std::unique_ptr<ShaderFactory> CreateShaderFactory()
{
    return std::make_unique<GLShaderFactory>();
}
} // namespace GLFactory
} // namespace FIRE
