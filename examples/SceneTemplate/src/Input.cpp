#include <SceneTemplate/Input.h>

#include <FIRE/Camera.h>
#include <FIRE/InputListener.h>
#include <FIRE/Window.h>

namespace SceneTemplate
{
void MapInput(FIRE::Camera& cam, FIRE::Window& window)
{
    auto input{std::make_shared<FIRE::InputListener>()};
    window.SetInputListener(input);
}
} // namespace SceneTemplate
