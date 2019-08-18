#ifndef FIRE_INPUTMAPPING_H
#define FIRE_INPUTMAPPING_H

namespace FIRE
{
class Window;
class SceneObject;
class Renderer;
} // namespace FIRE

namespace util
{
void MapInput(FIRE::Window& window, FIRE::SceneObject& sceneObject, FIRE::Renderer& renderer);
} // namespace util

#endif //FIRE_INPUTMAPPING_H
