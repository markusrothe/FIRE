#ifndef FIRE_MainLoop_h
#define FIRE_MainLoop_h

namespace FIRE
{
class Window;
class Scene;
class Renderer;
void MainLoop(
    Window& window,
    Scene& scene,
    Renderer& renderer);
} // namespace FIRE

#endif