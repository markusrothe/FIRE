#include "CubeSceneComponent.h"
#include <FIRE/Camera.h>
#include <FIRE/GLFactory.h>
#include <FIRE/MaterialFactory.h>
#include <FIRE/MeshManager.h>
#include <FIRE/ShaderFactory.h>
#include <FIRE/Window.h>
namespace examples
{
CubeSceneComponent::CubeSceneComponent(
    FIRE::Window const& window,
    FIRE::MeshManager& meshManager,
    FIRE::MaterialFactory& materialFactory)
    : m_proj(FIRE::CreatePerspectiveMatrix(70.0f, static_cast<float>(window.GetWidth()) / static_cast<float>(window.GetHeight()), 0.01f, 500.0f))
{

    m_cube.name = "cubeRenderable";
    m_cube.material = materialFactory.CreateDefaultMaterial();
    m_cube.mesh = meshManager.CreateCube("cube");

    m_cube.transform.Translate(0, 2, 0);
}

void CubeSceneComponent::Update(FIRE::Camera& cam)
{
    m_cube.transform.Rotate({1, 1, 1}, 1.0f);

    auto const MVP = m_proj * cam.ViewMatrix() * m_cube.transform.ModelMatrix();
    m_cube.material.SetShaderParameter("MVP", FIRE::ShaderParameterType::MAT4x4, MVP);
}

std::vector<FIRE::Renderable> CubeSceneComponent::CollectRenderables() const
{
    return {m_cube};
}
} // namespace examples
