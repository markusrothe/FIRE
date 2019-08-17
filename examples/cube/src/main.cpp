#include "FPSOverlayComponent.h"
#include "InputMappingComponent.h"
#include "PointLightComponent.h"
#include <FIRE/AssetFacade.h>
#include <FIRE/GLFactory.h>
#include <FIRE/InputListener.h>
#include <FIRE/MainLoop.h>
#include <FIRE/RenderContext.h>
#include <FIRE/Renderer.h>
#include <FIRE/Scene.h>
#include <FIRE/Window.h>

#include <FIRE/CameraComponent.h>
#include <FIRE/RenderingComponent.h>
#include <memory>
namespace
{

void SetupScene(
    FIRE::Window& window,
    FIRE::Scene& scene,
    FIRE::Renderer& renderer,
    FIRE::AssetFacade& assets)
{
    assets.SubmitShadersFromFiles(
        "phong",
        {{FIRE::ShaderType::VERTEX_SHADER, "PhongVS.glsl"}, {FIRE::ShaderType::FRAGMENT_SHADER, "PhongFS.glsl"}});

    auto input{std::make_shared<FIRE::InputListener>()};
    window.SetInputListener(input);

    auto cubeRenderables = assets.CreateRenderables("cube", 1u)
                               .WithMesh("cubeMesh", FIRE::MeshCategory::Cube)
                               .WithMaterial("phong")
                               .Build();

    auto& cubeObject = scene.CreateSceneObject("cube");
    cubeObject.AddComponent(std::make_unique<FIRE::RenderingComponent>(renderer, std::move(cubeRenderables)));
    cubeObject.GetTransform().SetPosition({0.0f, 4.0f, 0.0f});
    cubeObject.GetTransform().Scale({10.0f, 10.0f, 10.0f});

    auto& mainCamera = scene.CreateSceneObject("cam");
    mainCamera.AddComponent(std::make_unique<examples::InputMappingComponent>(mainCamera, *input, window, renderer));
    mainCamera.AddComponent(std::make_unique<FIRE::CameraComponent>(70.0f, static_cast<float>(window.GetWidth()) / static_cast<float>(window.GetHeight()), 0.1f, 3000.0f));
    mainCamera.GetTransform().SetPosition({20.0f, 20.0f, 20.0f});
    mainCamera.GetTransform().SetLookAt({0.0f, 0.0f, 0.0f});

    auto& sceneLight = scene.CreateSceneObject("light");
    sceneLight.AddComponent(std::make_unique<examples::PointLightComponent>());

    //auto& overlay = scene.CreateSceneObject("overlay");
    //overlay.AddComponent(std::make_unique<examples::FPSOverlayComponent>(renderer, assets));

    scene.Setup();
}

} // namespace

int main(int, char**)
{
    auto window{FIRE::GLFactory::CreateWindow("FIRE - cube", 800, 600)};
    auto assets{FIRE::GLFactory::CreateAssetFacade()};
    auto renderer{FIRE::GLFactory::CreateRenderer(assets)};

    FIRE::Scene scene;
    SetupScene(window, scene, *renderer, *assets);

    FIRE::MainLoop(window, scene, *renderer);
}
