#include "FPSOverlay.h"
#include "InputMapping.h"
#include <FIRE/FIRE.h>
#include <algorithm>
#include <memory>

namespace
{
void CreateCube(FIRE::Scene& scene, FIRE::AssetFacade& assets, FIRE::Renderer& renderer)
{
    assets.CreateMesh("cubeMesh", FIRE::MeshCategory::Cube);
    auto cubeRenderables = assets.CreateRenderables("cube", 1u)
                               .WithMesh("cubeMesh")
                               .WithMaterial("phong")
                               .Build();

    auto& cubeObject = scene.CreateSceneObject("cube");
    cubeObject.AddComponent(std::make_unique<FIRE::RenderingComponent>(renderer, std::move(cubeRenderables)));

    cubeObject.GetTransform().SetPosition({0.0f, 4.0f, 0.0f});
    cubeObject.GetTransform().Scale({10.0f, 10.0f, 10.0f});
}

void CreateCamera(FIRE::Window& window, FIRE::Scene& scene, FIRE::Renderer& renderer)
{
    auto& mainCamera = scene.CreateSceneObject("cam");
    mainCamera.AddComponent(std::make_unique<FIRE::InputComponent>(window));
    util::MapInput(window, mainCamera, renderer);

    mainCamera.AddComponent(std::make_unique<FIRE::CameraComponent>(
        70.0f, static_cast<float>(window.GetWidth()) / static_cast<float>(window.GetHeight()), 0.1f, 3000.0f));

    mainCamera.GetTransform().SetPosition({20.0f, 20.0f, 20.0f});
    mainCamera.GetTransform().SetLookAt({0.0f, 0.0f, 0.0f});
}

void CreateLight(FIRE::Scene& scene)
{
    auto& sceneLight = scene.CreateSceneObject("light");
    sceneLight.AddComponent(std::make_unique<FIRE::LightComponent>());
    sceneLight.GetTransform().SetPosition({0.0f, 100.0f, 0.0f});
}

void CreateOverlays(FIRE::Scene& scene, FIRE::AssetFacade& assets, FIRE::Renderer& renderer)
{
    auto& overlay = scene.CreateSceneObject("overlay");
    auto overlays = assets.CreateTextOverlays("textoverlay", 2u)
                        .WithText("")
                        .At(0.01f, 0.01f)
                        .ScaledBy(0.5f)
                        .WithText("FIRE cube")
                        .At(0.01f, 0.95f)
                        .ScaledBy(0.5f)
                        .Build();
    overlay.AddComponent(std::make_unique<util::FPSOverlay>(renderer, overlays));
}
} // namespace

int main(int, char**)
{
    auto window{FIRE::GLFactory::CreateWindow("FIRE - cube", 800, 600)};
    auto assets{FIRE::GLFactory::CreateAssetFacade()};
    auto renderer{FIRE::GLFactory::CreateRenderer(assets)};

    FIRE::Scene scene;

    FIRE::Shaders shaders = {
        FIRE::ShaderDescriptor{FIRE::ShaderType::VERTEX_SHADER, std::filesystem::path("./PhongVS.glsl")},
        FIRE::ShaderDescriptor{FIRE::ShaderType::FRAGMENT_SHADER, std::filesystem::path("./PhongFS.glsl")}};

    assets->SubmitShadersFromFiles("phong", shaders);

    CreateCube(scene, *assets, *renderer);
    CreateCamera(window, scene, *renderer);
    CreateLight(scene);
    CreateOverlays(scene, *assets, *renderer);

    FIRE::MainLoop(window, scene, *renderer);
}
