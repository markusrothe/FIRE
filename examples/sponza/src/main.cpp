
#include "FPSOverlayComponent.h"
#include <FIRE/AssetFacade.h>
#include <FIRE/CameraComponent.h>
#include <FIRE/GLFactory.h>
#include <FIRE/InputComponent.h>
#include <FIRE/InputListener.h>
#include <FIRE/LightComponent.h>
#include <FIRE/MainLoop.h>
#include <FIRE/RenderContext.h>
#include <FIRE/Renderer.h>
#include <FIRE/RenderingComponent.h>
#include <FIRE/Scene.h>
#include <FIRE/Window.h>

#include <memory>
namespace
{
unsigned int constexpr WINDOW_WIDTH = 1920;
unsigned int constexpr WINDOW_HEIGHT = 1080;
} // namespace

int main(int, char**)
{
    FIRE::Window window = FIRE::GLFactory::CreateWindow("FIRE - sponza", WINDOW_WIDTH, WINDOW_HEIGHT);

    auto assets{FIRE::GLFactory::CreateAssetFacade()};
    auto renderer{FIRE::GLFactory::CreateRenderer(assets)};

    FIRE::Scene scene;

    assets->SubmitShadersFromFiles(
        "texSampling",
        {{FIRE::ShaderType::VERTEX_SHADER, "textureSamplingVS.glsl"}, {FIRE::ShaderType::FRAGMENT_SHADER, "textureSamplingFS.glsl"}});

    assets->SubmitModelFromFile("sponza", "sponza.obj");
    auto renderables = assets->CreateModelRenderables("sponza", "sponza", "texSampling");

    auto& sponzaObj = scene.CreateSceneObject("sponza");
    sponzaObj.AddComponent(std::make_unique<FIRE::RenderingComponent>(*renderer, std::move(renderables)));

    auto& mainCamera = scene.CreateSceneObject("cam");
    mainCamera.AddComponent(std::make_unique<FIRE::InputComponent>(window));
    mainCamera.AddComponent(std::make_unique<FIRE::CameraComponent>(
        70.0f, static_cast<float>(window.GetWidth()) / static_cast<float>(window.GetHeight()), 0.1f, 3000.0f));

    auto& sceneLight = scene.CreateSceneObject("light");
    sceneLight.AddComponent(std::make_unique<FIRE::LightComponent>());

    //    auto& overlay = scene.CreateSceneObject("overlay");
    //    overlay.AddComponent(std::make_unique<examples::FPSOverlayComponent>(renderer, assets));

    FIRE::MainLoop(window, scene, *renderer);
}
