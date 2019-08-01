
#include "GLShaderFactory.h"

#include "FIRE/Renderer.h"
#include "GLDraw.h"
#include "GLFontTextureFactory.h"
#include "GLImageTextureFactory.h"
#include "GLMaterialBinder.h"
#include "GLRenderContext.h"
#include "GLVertexLayoutFactory.h"
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

std::unique_ptr<Renderer> CreateRenderer()
{

    auto layoutFactory = std::make_unique<GLVertexLayoutFactory>();
    auto materialBinder = std::make_unique<GLMaterialBinder>();
    auto draw = std::make_unique<GLDraw>();

    //    auto texFactory = std::make_unique<TextureFactory>(
    //        std::make_unique<GLImageTextureFactory>(),
    //        std::make_unique<GLFontTextureFactory>());
    //    auto textOverlayRenderer = std::make_unique<GLTextOverlayRenderer>(std::move(texFactory));

    return std::make_unique<Renderer>(
        std::move(draw),
        std::move(materialBinder),
        std::move(layoutFactory));
}

std::unique_ptr<ShaderFactory> CreateShaderFactory()
{
    return std::make_unique<GLShaderFactory>();
}
} // namespace FIRE::GLFactory
