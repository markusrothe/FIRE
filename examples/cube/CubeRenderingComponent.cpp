#include "CubeRenderingComponent.h"

#include <FIRE/CameraComponent.h>
#include <FIRE/MaterialFactory.h>
#include <FIRE/MeshManager.h>
#include <FIRE/Message.h>
#include <FIRE/Scene.h>
#include <FIRE/SceneObject.h>
#include <FIRE/Window.h>

namespace examples
{

CubeRenderingComponent::CubeRenderingComponent(FIRE::Renderer& renderer, FIRE::MeshManager& meshManager, FIRE::MaterialFactory& materialFactory)
    : FIRE::RenderingComponent(renderer)
{
    m_cube.name = "cubeRenderable";
    m_cube.material = materialFactory.CreateDefaultMaterial();
    m_cube.mesh = meshManager.CreateCube("cube");
}

void CubeRenderingComponent::DoUpdate(FIRE::SceneObject& sceneObject, FIRE::Scene& scene)
{
    auto& transform = sceneObject.GetTransform();
    transform.SetPosition({0, 2, 0});
    transform.Rotate({1, 1, 1}, 1.0f);

    auto viewMatrix = std::any_cast<glm::mat4x4>(scene.Send(FIRE::Message(0)).value());
    auto projMatrix = std::any_cast<glm::mat4x4>(scene.Send(FIRE::Message(1)).value());

    auto const MVP = projMatrix * viewMatrix * transform.ModelMatrix();
    m_cube.material.SetShaderParameter("MVP", FIRE::ShaderParameterType::MAT4x4, MVP);

    m_renderer.Submit(m_cube);
}

std::optional<std::any> CubeRenderingComponent::Receive(FIRE::Message)
{
    return std::nullopt;
}

} // namespace examples
