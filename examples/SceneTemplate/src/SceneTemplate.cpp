#include <SceneTemplate/Input.h>
#include <SceneTemplate/SceneTemplate.h>

#include <FIRE/Camera.h>
#include <FIRE/GLFactory.h>
#include <FIRE/MaterialFactory.h>
#include <FIRE/Mesh.h>
#include <FIRE/MeshFactory.h>
#include <FIRE/ShaderFactory.h>
#include <FIRE/Window.h>
#include <fstream>
#include <iterator>
#include <string>

namespace SceneTemplate
{
namespace
{
std::string const PLANE{"plane"};
std::string const LIGHT{"light"};

std::string GetFileContent(std::string const& filePath)
{
    std::ifstream file(filePath);
    std::string const content{(std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()};
    return content;
}

FIRE::Material CreateDefaultMaterial()
{
    auto shaderFactory{FIRE::GLFactory::CreateShaderFactory()};
    return FIRE::MaterialFactory::CreateDefault(*shaderFactory);
}

FIRE::Material CreatePhongMaterial()
{
    auto shaderFactory{FIRE::GLFactory::CreateShaderFactory()};

    FIRE::Shaders const shaders = {
        {FIRE::ShaderType::VERTEX_SHADER, GetFileContent("PhongVS.glsl")},
        {FIRE::ShaderType::FRAGMENT_SHADER, GetFileContent("PhongFS.glsl")}};

    return FIRE::MaterialFactory::Create("phong", shaders, *shaderFactory);
}

} // namespace

FIRE::Renderable CreatePlane(FIRE::MeshFactory& factory, FIRE::Material material)
{
    FIRE::Renderable plane;
    plane.name = PLANE;
    plane.mesh = factory.CreatePlane(PLANE);
    plane.material = material;

    return plane;
}

FIRE::Renderable CreateCube(FIRE::MeshFactory& factory, FIRE::Material material)
{
    FIRE::Renderable renderable;
    renderable.name = LIGHT;
    renderable.mesh = factory.CreateCube(LIGHT);
    renderable.material = material;
    return renderable;
}

SceneTemplate::SceneTemplate(FIRE::Camera& cam, FIRE::Window& window, FIRE::MeshFactory& factory)
    : m_lightPos{5.0f, 10.0f, 7.0f}
    , m_proj(FIRE::CreatePerspectiveMatrix(70.0f, static_cast<float>(window.GetWidth()) / static_cast<float>(window.GetHeight()), 0.01f, 500.0f))
{
    MapInput(cam, window);

    m_plane = CreatePlane(factory, CreatePhongMaterial());
    m_plane.transform.Scale(FIRE::Vector3(20.0f, 1.0f, 20.0f));
    m_plane.material.SetShaderParameter("LightPos", FIRE::ShaderParameterType::VEC3, m_lightPos);

    m_lightCube = CreateCube(factory, CreateDefaultMaterial());
    m_lightCube.transform.Translate(m_lightPos);
    m_lightCube.transform.Scale({0.1f, 0.1f, 0.1f});
}

void SceneTemplate::Update(FIRE::Camera& cam)
{
    auto VP = m_proj * cam.ViewMatrix();

    m_plane.material.SetShaderParameter("M", FIRE::ShaderParameterType::MAT4x4, m_plane.transform.ModelMatrix());
    m_plane.material.SetShaderParameter("VP", FIRE::ShaderParameterType::MAT4x4, VP);

    m_lightCube.material.SetShaderParameter("MVP", FIRE::ShaderParameterType::MAT4x4, VP * m_lightCube.transform.ModelMatrix());
}

std::vector<FIRE::Renderable> SceneTemplate::CollectRenderables() const
{
    return {m_plane, m_lightCube};
}
} // namespace SceneTemplate
