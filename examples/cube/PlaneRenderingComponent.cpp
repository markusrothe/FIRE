#include "PlaneRenderingComponent.h"
#include <FIRE/MaterialFactory.h>
#include <FIRE/MeshManager.h>
#include <FIRE/Message.h>
#include <FIRE/Scene.h>
#include <FIRE/SceneObject.h>
#include <FIRE/Window.h>

namespace examples
{
PlaneRenderingComponent::PlaneRenderingComponent(
    FIRE::SceneObject& sceneObject,
    FIRE::Renderer& renderer,
    FIRE::MeshManager& meshManager,
    FIRE::MaterialFactory& materialFactory)
    : FIRE::RenderingComponent(renderer)
{
    auto& transform = sceneObject.GetTransform();
    transform.Scale({100.0f, 1.0f, 100.0f});

    m_plane.name = "planeRenderable";
    m_plane.material = materialFactory.CreateDefaultMaterial();
    m_plane.mesh = meshManager.CreatePlane("plane");
}

void PlaneRenderingComponent::DoUpdate(double, FIRE::SceneObject& sceneObject, FIRE::Scene& scene)
{
    auto viewMatrix = std::any_cast<glm::mat4x4>(scene.Send(FIRE::Message(0)).value());
    auto projMatrix = std::any_cast<glm::mat4x4>(scene.Send(FIRE::Message(1)).value());

    m_plane.material.SetShaderParameter("MVP", FIRE::ShaderParameterType::MAT4x4, projMatrix * viewMatrix * sceneObject.GetTransform().ModelMatrix());

    m_renderer.Submit(m_plane);
}

std::optional<std::any> PlaneRenderingComponent::Receive(FIRE::Message)
{
    return std::nullopt;
}
} // namespace examples
