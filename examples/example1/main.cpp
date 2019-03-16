#include <FIRE/GLRenderContext.h>
#include <FIRE/Window.h>

int main(int, char**)
{
    FIRE::Window window{"example1", 800, 600};

    auto context{std::make_unique<FIRE::GLRenderContext>(window)};

    window.SetRenderContext(std::move(context));

    while(!window.ShouldClose())
    {
        window.SwapBuffers();
    }
}
