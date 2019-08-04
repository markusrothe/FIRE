
#include "GLShaderFactory.h"

#include "FIRE/Renderer.h"
#include "FIRE/TextureManager.h"
#include "FTFontLoader.h"
#include "GLDraw.h"
#include "GLMaterialBinder.h"
#include "GLRenderContext.h"
#include "GLTextureFactory.h"
#include "GLVertexLayoutFactory.h"
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

std::unique_ptr<Renderer> CreateRenderer(std::shared_ptr<TextureManager> texManager)
{
    return std::make_unique<Renderer>(
        std::make_unique<GLDraw>(),
        std::make_unique<GLMaterialBinder>(),
        std::make_unique<GLVertexLayoutFactory>(),
        std::move(texManager));
}

MaterialFactory CreateMaterialFactory()
{
    return MaterialFactory(std::make_unique<GLShaderFactory>());
}

std::unique_ptr<TextureManager> CreateTextureManager()
{
    return std::make_unique<TextureManager>(
        std::make_unique<GLTextureFactory>(),
        std::make_unique<FTFontLoader>());
}

} // namespace FIRE::GLFactory
