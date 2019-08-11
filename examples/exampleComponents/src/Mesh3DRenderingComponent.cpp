#include "Mesh3DRenderingComponent.h"

#include <FIRE/Message.h>
#include <FIRE/Scene.h>
#include <FIRE/SceneObject.h>
#include <FIRE/Window.h>
namespace examples
{

Mesh3DRenderingComponent::Mesh3DRenderingComponent(
    FIRE::Renderer& renderer,
    std::vector<FIRE::Renderable>&& renderables)
    : FIRE::RenderingComponent(renderer)
    , renderables(std::move(renderables))
{
}

void Mesh3DRenderingComponent::DoUpdate(double, FIRE::SceneObject& sceneObject, FIRE::Scene& scene)
{
    auto& transform = sceneObject.GetTransform();
    transform.Rotate({1, 1, 1}, 0.1f);
    auto viewMatrix = std::any_cast<glm::mat4x4>(scene.Send(FIRE::Message(0)).value());
    auto projMatrix = std::any_cast<glm::mat4x4>(scene.Send(FIRE::Message(1)).value());
    auto lightPos = std::any_cast<glm::vec3>(scene.Send(FIRE::Message(2)).value());
    for(auto& renderable : renderables)
    {
        renderable.material.SetShaderParameter("M", FIRE::ShaderParameterType::MAT4x4, transform.ModelMatrix());
        renderable.material.SetShaderParameter("VP", FIRE::ShaderParameterType::MAT4x4, projMatrix * viewMatrix);
        renderable.material.SetShaderParameter("LightPos", FIRE::ShaderParameterType::VEC3, lightPos);
        m_renderer.Submit(renderable);
    }
}

std::optional<std::any> Mesh3DRenderingComponent::Receive(FIRE::Message, FIRE::SceneObject&)
{
    return std::nullopt;
}

} // namespace examples
