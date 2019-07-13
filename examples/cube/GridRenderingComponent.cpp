#include "GridRenderingComponent.h"
#include <FIRE/MaterialFactory.h>
#include <FIRE/MeshManager.h>
#include <FIRE/Message.h>
#include <FIRE/Scene.h>
#include <FIRE/SceneObject.h>
#include <FIRE/Window.h>
#include <fstream>
#include <random>
#include <sstream>

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

GridRenderingComponent::GridRenderingComponent(
    FIRE::SceneObject& sceneObject,
    FIRE::Renderer& renderer,
    FIRE::MeshManager& meshManager,
    FIRE::MaterialFactory& materialFactory)
    : FIRE::RenderingComponent(renderer)
{

    std::vector<glm::vec3> positions, normals;
    std::vector<unsigned int> indices;

    unsigned int count = 0;
    for(auto j = 1.0f; j > -1.0f; j -= 0.01f)
    {
        for(auto i = -1.0f; i < 1.0f; i += 0.01f)
        {
            positions.emplace_back(i, 0.0f, j);
            positions.emplace_back(i + 0.01f, 0.0f, j);
            positions.emplace_back(i, 0.0f, j - 0.01f);
            positions.emplace_back(i + 0.01f, 0.0f, j);
            positions.emplace_back(i + 0.01f, 0.0f, j - 0.01f);
            positions.emplace_back(i, 0.0f, j - 0.01f);

            normals.emplace_back(0.0f, 1.0f, 0.0f);
            normals.emplace_back(0.0f, 1.0f, 0.0f);
            normals.emplace_back(0.0f, 1.0f, 0.0f);
            normals.emplace_back(0.0f, 1.0f, 0.0f);
            normals.emplace_back(0.0f, 1.0f, 0.0f);
            normals.emplace_back(0.0f, 1.0f, 0.0f);

            indices.push_back(count++);
            indices.push_back(count++);
            indices.push_back(count++);
            indices.push_back(count++);
            indices.push_back(count++);
            indices.push_back(count++);
        }
    }

    auto& transform = sceneObject.GetTransform();
    transform.Scale({1000.0f, 1.0f, 1000.0f});

    m_plane.name = "gridRenderable";
    m_plane.material = materialFactory.CreateDefaultMaterial();
    m_plane.mesh = meshManager.Create(
        FIRE::MeshCategory::Custom, FIRE::MeshPrimitives::Triangles, "grid", std::move(positions), std::move(normals), std::move(indices));
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
