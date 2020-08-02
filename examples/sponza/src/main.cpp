#include "InputMapping.h"
#include <FIRE/FIRE.h>

#include <memory>
namespace
{
unsigned int constexpr WINDOW_WIDTH = 1920;
unsigned int constexpr WINDOW_HEIGHT = 1080;

void CreateRenderables(FIRE::Scene& scene, FIRE::AssetFacade& assets, FIRE::Renderer& renderer)
{
    assets.SubmitModelFromFile("sponza", "sponza.obj");
    auto renderables = assets.CreateModelRenderables("sponza", "sponza", "texSampling");
    auto& sponzaObj = scene.CreateSceneObject("sponza");
    sponzaObj.AddComponent(std::make_unique<FIRE::RenderingComponent>(renderer, std::move(renderables)));
}

void CreateLight(FIRE::Scene& scene)
{
    auto& sceneLight = scene.CreateSceneObject("light");
    sceneLight.AddComponent(std::make_unique<FIRE::LightComponent>());
}

void CreateCamera(FIRE::Scene& scene, FIRE::Window& window, FIRE::Renderer& renderer)
{
    auto& mainCamera = scene.CreateSceneObject("cam");
    mainCamera.AddComponent(std::make_unique<FIRE::InputComponent>(window));
    util::MapInput(window, mainCamera, renderer);
    mainCamera.AddComponent(std::make_unique<FIRE::CameraComponent>(
        70.0f, static_cast<float>(window.GetWidth()) / static_cast<float>(window.GetHeight()), 0.1f, 3000.0f));
}
} // namespace

int main(int, char**)
{
    FIRE::Window window = FIRE::GLFactory::CreateWindow("FIRE - sponza", WINDOW_WIDTH, WINDOW_HEIGHT);

    auto assets{FIRE::GLFactory::CreateAssetFacade()};
    auto renderer{FIRE::GLFactory::CreateRenderer(assets)};

    FIRE::Shaders shaders = {
        FIRE::ShaderDescriptor{FIRE::ShaderType::VERTEX_SHADER, std::filesystem::path("textureSamplingVS.glsl")},
        FIRE::ShaderDescriptor{FIRE::ShaderType::FRAGMENT_SHADER, std::filesystem::path("textureSamplingFS.glsl")},
    };
    assets->SubmitShadersFromFiles("texSampling", shaders);

    FIRE::Scene scene;
    CreateRenderables(scene, *assets, *renderer);
    CreateCamera(scene, window, *renderer);
    CreateLight(scene);

    FIRE::MainLoop(window, scene, *renderer);
}
