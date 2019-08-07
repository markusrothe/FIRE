#include "FPSOverlayComponent.h"
#include "InputMappingComponent.h"
#include "Mesh3DRenderingComponent.h"
#include "PerspectiveCameraComponent.h"
#include "PointLightComponent.h"
#include <FIRE/GLFactory.h>
#include <FIRE/InputListener.h>
#include <FIRE/MainLoop.h>
#include <FIRE/MaterialFactory.h>
#include <FIRE/MeshManager.h>
#include <FIRE/RenderContext.h>
#include <FIRE/Renderer.h>
#include <FIRE/Scene.h>
#include <FIRE/Window.h>

#include <FIRE/TextureManager.h>
#include <memory>
namespace
{
unsigned int constexpr WINDOW_WIDTH = 800;
unsigned int constexpr WINDOW_HEIGHT = 600;

void SubmitShaders(FIRE::MaterialFactory& materialFactory)
{
    materialFactory.CreateMaterialFromFiles("phong", "PhongVS.glsl", "PhongFS.glsl");
    materialFactory.CreateMaterialFromFiles("height", "HeightVS.glsl", "HeightFS.glsl");
    materialFactory.CreateMaterialFromFiles("grid", "GridVS.glsl", "GridFS.glsl");
    materialFactory.CreateMaterialFromFiles("texCoords", "texCoordsVS.glsl", "texCoordsFS.glsl");
    materialFactory.CreateMaterialFromFiles("texSampling", "textureSamplingVS.glsl", "textureSamplingFS.glsl");
    materialFactory.CreateMaterialFromFiles("text", "textVS.glsl", "textFS.glsl");
}

void SetupScene(
    FIRE::Window& window,
    FIRE::Scene& scene,
    FIRE::Renderer& renderer,
    FIRE::MaterialFactory& materialFactory,
    FIRE::MeshManager& meshManager,
    FIRE::TextureManager& texManager)
{
    auto input{std::make_shared<FIRE::InputListener>()};
    window.SetInputListener(input);

    auto& cubeObject = scene.CreateSceneObject("cube");

    auto textureMaterial = materialFactory.GetMaterial("texSampling");
    auto checkerBoardTexture = texManager.CreateImageTexture("checkerBoardTex", 2, 2, {0x00, 0xff, 0xff, 0x00}, 1, FIRE::Texture2D::WrappingMode::CLAMP, FIRE::Texture2D::Filter::NEAREST);
    textureMaterial.AddTexture(checkerBoardTexture, 0u);

    std::vector<FIRE::Renderable> renderables;
    renderables.emplace_back("cubeRenderable", textureMaterial, meshManager.CreateCube("cubeMesh"));
    cubeObject.AddComponent(std::make_unique<examples::Mesh3DRenderingComponent>(renderer, std::move(renderables)));

    auto& mainCamera = scene.CreateSceneObject("cam");
    mainCamera.AddComponent(
        std::make_unique<examples::InputMappingComponent>(mainCamera, *input, window, renderer));

    mainCamera.AddComponent(
        std::make_unique<examples::PerspectiveCameraComponent>(
            70.0f, static_cast<float>(window.GetWidth()) / static_cast<float>(window.GetHeight()), 0.1f, 3000.0f));

    auto& sceneLight = scene.CreateSceneObject("light");
    sceneLight.AddComponent(std::make_unique<examples::PointLightComponent>());

    auto& overlay = scene.CreateSceneObject("overlay");

    overlay.AddComponent(std::make_unique<examples::FPSOverlayComponent>(renderer, materialFactory));

    scene.Setup();
}

} // namespace

int main(int, char**)
{
    FIRE::Window window = FIRE::GLFactory::InitWindow("FIRE - cube", WINDOW_WIDTH, WINDOW_HEIGHT);

    auto materialFactory = FIRE::GLFactory::CreateMaterialFactory();
    SubmitShaders(materialFactory);

    std::shared_ptr<FIRE::TextureManager> textureManager = FIRE::GLFactory::CreateTextureManager();
    FIRE::MeshManager meshManager;
    auto renderer{FIRE::GLFactory::CreateRenderer(textureManager)};

    FIRE::Scene scene;
    SetupScene(window, scene, *renderer, materialFactory, meshManager, *textureManager);

    FIRE::MainLoop(window, scene, *renderer);
}
