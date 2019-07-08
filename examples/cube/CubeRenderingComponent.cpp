#include "CubeRenderingComponent.h"

#include <FIRE/CameraComponent.h>
#include <FIRE/MaterialFactory.h>
#include <FIRE/MeshManager.h>
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

    FIRE::CameraComponent const* cam = scene.GetCamera();

    auto const MVP = cam->GetProjectionMatrix() * cam->GetViewMatrix() * transform.ModelMatrix();
    m_cube.material.SetShaderParameter("MVP", FIRE::ShaderParameterType::MAT4x4, MVP);

    m_renderer.Submit(m_cube);
}

} // namespace examples
