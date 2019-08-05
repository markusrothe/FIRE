#include "FIRE/Renderer.h"
#include <FIRE/MainLoop.h>
#include <FIRE/Scene.h>
#include <FIRE/Window.h>
#include <chrono>
using namespace std::chrono_literals;

namespace FIRE
{
void MainLoop(
    Window& window,
    Scene& scene,
    Renderer& renderer)
{
    auto const width = static_cast<float>(window.GetWidth());
    auto const height = static_cast<float>(window.GetHeight());
    auto lastTime = std::chrono::high_resolution_clock::now();
    std::chrono::nanoseconds lag{0ns};
    std::chrono::nanoseconds timestep{16ms};
    while(!window.ShouldClose())
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto deltaTime = currentTime - lastTime;

        lastTime = currentTime;
        lag += deltaTime;
        window.PollEvents();

        while(lag >= timestep)
        {
            scene.Update(std::chrono::duration<double>(lag).count());
            lag -= timestep;
        }

        renderer.Render(width, height);
        window.SwapBuffers();
    }
}
} // namespace FIRE
