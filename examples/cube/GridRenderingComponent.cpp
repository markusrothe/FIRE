#include "GridRenderingComponent.h"
#include <FIRE/MaterialFactory.h>
#include <FIRE/MeshManager.h>
#include <FIRE/Message.h>
#include <FIRE/Noise.h>
#include <FIRE/Scene.h>
#include <FIRE/SceneObject.h>
#include <FIRE/Window.h>
#include <fstream>
#include <random>
#include <sstream>

namespace examples
{

GridRenderingComponent::GridRenderingComponent(
    FIRE::SceneObject& sceneObject,
    FIRE::Renderer& renderer,
    FIRE::MeshManager& meshManager,
    FIRE::MaterialFactory& materialFactory)
    : FIRE::RenderingComponent(renderer)
{
    m_plane.mesh = meshManager.CreateTriangleGrid("TriangleGrid", 100, 100);

    auto& transform = sceneObject.GetTransform();
    transform.Scale({1000.0f, 1.0f, 1000.0f});

    m_plane.name = "gridRenderable";
    m_plane.material = materialFactory.CreateDefaultMaterial();
}

void GridRenderingComponent::DoUpdate(double, FIRE::SceneObject& sceneObject, FIRE::Scene& scene)
{
    auto transform = sceneObject.GetTransform();
    auto viewMatrix = std::any_cast<glm::mat4x4>(scene.Send(FIRE::Message(0)).value());
    auto projMatrix = std::any_cast<glm::mat4x4>(scene.Send(FIRE::Message(1)).value());

    m_plane.material.SetShaderParameter("MVP", FIRE::ShaderParameterType::MAT4x4, projMatrix * viewMatrix * transform.ModelMatrix());

    m_renderer.Submit(m_plane);
}

std::optional<std::any> GridRenderingComponent::Receive(FIRE::Message)
{
    return std::nullopt;
}
} // namespace examples
