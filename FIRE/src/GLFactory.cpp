
#include "GLShaderFactory.h"

#include "GLDrawAgent.h"
#include "GLFontTextureFactory.h"
#include "GLImageTextureFactory.h"
#include "GLRenderContext.h"
#include "GLRenderer.h"
#include "GLUploader.h"
#include "TextureFactory.h"
#include <FIRE/GLFactory.h>
#include <FIRE/Window.h>

namespace FIRE::GLFactory
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
        std::make_unique<GLDrawAgent>(meshManager),
        std::make_unique<TextureFactory>(
            std::make_unique<GLImageTextureFactory>(),
            std::make_unique<GLFontTextureFactory>()));
}

std::unique_ptr<ShaderFactory> CreateShaderFactory()
{
    return std::make_unique<GLShaderFactory>();
}
} // namespace FIRE::GLFactory
