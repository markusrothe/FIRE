#include "CubeRenderingComponent.h"

#include <FIRE/MaterialFactory.h>
#include <FIRE/MeshManager.h>
#include <FIRE/Message.h>
#include <FIRE/Scene.h>
#include <FIRE/SceneObject.h>
#include <FIRE/Window.h>
#include <fstream>
#include <iterator>
#include <string>

namespace examples
{
namespace
{
std::string GetFileContent(std::string const& filePath)
{
    std::ifstream file(filePath);
    std::string const content{(std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()};
    return content;
}
} // namespace

CubeRenderingComponent::CubeRenderingComponent(FIRE::Renderer& renderer, FIRE::MeshManager& meshManager, FIRE::MaterialFactory& materialFactory)
    : FIRE::RenderingComponent(renderer)
{
    m_cube.name = "cubeRenderable";

    FIRE::Shaders const shaders = {
        {FIRE::ShaderType::VERTEX_SHADER, GetFileContent("PhongVS.glsl")},
        {FIRE::ShaderType::FRAGMENT_SHADER, GetFileContent("PhongFS.glsl")}};
    m_cube.material = materialFactory.CreateMaterial("phong", shaders);

    m_cube.mesh = meshManager.CreateCube("cube");
}

void CubeRenderingComponent::DoUpdate(double deltaTime, FIRE::SceneObject& sceneObject, FIRE::Scene& scene)
{
    auto& transform = sceneObject.GetTransform();
    transform.SetPosition({0, 2, 0});
    transform.Rotate({1, 1, 1}, 100.0f * static_cast<float>(deltaTime));

    auto viewMatrix = std::any_cast<glm::mat4x4>(scene.Send(FIRE::Message(0)).value());
    auto projMatrix = std::any_cast<glm::mat4x4>(scene.Send(FIRE::Message(1)).value());
    auto lightPos = std::any_cast<glm::vec3>(scene.Send(FIRE::Message(2)).value());

    m_cube.material.SetShaderParameter("M", FIRE::ShaderParameterType::MAT4x4, transform.ModelMatrix());
    m_cube.material.SetShaderParameter("VP", FIRE::ShaderParameterType::MAT4x4, projMatrix * viewMatrix);
    m_cube.material.SetShaderParameter("LightPos", FIRE::ShaderParameterType::VEC3, lightPos);

    m_renderer.Submit(m_cube);
}

std::optional<std::any> CubeRenderingComponent::Receive(FIRE::Message)
{
    return std::nullopt;
}

} // namespace examples
