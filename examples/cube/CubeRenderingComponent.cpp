#include "CubeRenderingComponent.h"

#include <FIRE/MaterialFactory.h>
#include <FIRE/MeshManager.h>
#include <FIRE/Message.h>
#include <FIRE/Scene.h>
#include <FIRE/SceneObject.h>
#include <FIRE/Window.h>
#include <fstream>
#include <iterator>
#include <sstream>
#include <string>

namespace examples
{

CubeRenderingComponent::CubeRenderingComponent(FIRE::Renderer& renderer, FIRE::MeshManager& meshManager, FIRE::MaterialFactory& materialFactory)
    : FIRE::RenderingComponent(renderer)
{
    auto meshHandles = meshManager.CreateFromFile("sponza", "sponza.obj");
    int i = 0;
    for(auto handle : meshHandles)
    {
        std::stringstream ss;
        ss << "sponza_mesh_" << i++;
        FIRE::Renderable r;
        r.name = ss.str();
        r.material = materialFactory.GetMaterial("phong");
        r.mesh = handle;
        renderables.push_back(r);
    }
    m_cube.name = "cubeRenderable";
    m_cube.material = materialFactory.GetMaterial("phong");
    m_cube.mesh = meshManager.CreateCube("cube");
}

void CubeRenderingComponent::DoUpdate(double, FIRE::SceneObject& sceneObject, FIRE::Scene& scene)
{
    auto& transform = sceneObject.GetTransform();
    //transform.SetPosition({0, 2, 0});
    //transform.Rotate({1, 1, 1}, 100.0f * static_cast<float>(deltaTime));

    auto viewMatrix = std::any_cast<glm::mat4x4>(scene.Send(FIRE::Message(0)).value());
    auto projMatrix = std::any_cast<glm::mat4x4>(scene.Send(FIRE::Message(1)).value());
    auto lightPos = std::any_cast<glm::vec3>(scene.Send(FIRE::Message(2)).value());

    m_cube.material.SetShaderParameter("M", FIRE::ShaderParameterType::MAT4x4, transform.ModelMatrix());
    m_cube.material.SetShaderParameter("VP", FIRE::ShaderParameterType::MAT4x4, projMatrix * viewMatrix);
    m_cube.material.SetShaderParameter("LightPos", FIRE::ShaderParameterType::VEC3, lightPos);

    for(auto& renderable : renderables)
    {
        renderable.material.SetShaderParameter("M", FIRE::ShaderParameterType::MAT4x4, transform.ModelMatrix());
        renderable.material.SetShaderParameter("VP", FIRE::ShaderParameterType::MAT4x4, projMatrix * viewMatrix);
        renderable.material.SetShaderParameter("LightPos", FIRE::ShaderParameterType::VEC3, lightPos);
        m_renderer.Submit(renderable);
    }

    m_renderer.Submit(m_cube);
}

std::optional<std::any> CubeRenderingComponent::Receive(FIRE::Message)
{
    return std::nullopt;
}

} // namespace examples
