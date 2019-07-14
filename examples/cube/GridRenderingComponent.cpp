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

    std::vector<glm::vec3> positions, normals;
    std::vector<unsigned int> indices;

    auto heightmap = FIRE::Noise::CreateHeightmap(1001, 1001);
    unsigned int count = 0;
    unsigned int y = 999;
    for(auto j = 1.0f; j > -1.0f; j -= 0.01f)
    {
        unsigned int x = 0;
        for(auto i = -1.0f; i < 1.0f; i += 0.01f)
        {

            positions.emplace_back(i, heightmap[x][y], j);
            positions.emplace_back(i + 0.01f, heightmap[x + 1][y], j);
            positions.emplace_back(i, heightmap[x][y - 1], j - 0.01f);
            positions.emplace_back(i + 0.01f, heightmap[x + 1][y], j);
            positions.emplace_back(i + 0.01f, heightmap[x + 1][y - 1], j - 0.01f);
            positions.emplace_back(i, heightmap[x][y - 1], j - 0.01f);

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
            x++;
        }
        y--;
    }

    auto& transform = sceneObject.GetTransform();
    transform.Scale({1000.0f, 100.0f, 1000.0f});

    m_plane.name = "gridRenderable";
    FIRE::Shaders const shaders = {
        {FIRE::ShaderType::VERTEX_SHADER, "HeightVS.glsl"},
        {FIRE::ShaderType::FRAGMENT_SHADER, "HeightFS.glsl"}};

    auto mat = materialFactory.CreateMaterialFromFiles("phong", shaders);
    //auto mat = materialFactory.CreateDefaultMaterial();
    m_plane.material = mat;
    m_plane.mesh = meshManager.Create(
        FIRE::MeshCategory::Custom, FIRE::MeshPrimitives::Triangles, "grid", std::move(positions), std::move(normals), std::move(indices));
}

void GridRenderingComponent::DoUpdate(double, FIRE::SceneObject& sceneObject, FIRE::Scene& scene)
{
    auto transform = sceneObject.GetTransform();
    auto viewMatrix = std::any_cast<glm::mat4x4>(scene.Send(FIRE::Message(0)).value());
    auto projMatrix = std::any_cast<glm::mat4x4>(scene.Send(FIRE::Message(1)).value());

    //m_plane.material.SetShaderParameter("MVP", FIRE::ShaderParameterType::MAT4x4, projMatrix * viewMatrix * transform.ModelMatrix());
    m_plane.material.SetShaderParameter("M", FIRE::ShaderParameterType::MAT4x4, transform.ModelMatrix());
    m_plane.material.SetShaderParameter("VP", FIRE::ShaderParameterType::MAT4x4, projMatrix * viewMatrix);

    m_renderer.Submit(m_plane);
}

std::optional<std::any> GridRenderingComponent::Receive(FIRE::Message)
{
    return std::nullopt;
}
} // namespace examples
