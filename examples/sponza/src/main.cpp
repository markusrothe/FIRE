
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
#include <FIRE/SceneObject.h>
#include <FIRE/Window.h>

#include <memory>
#include <sstream>
namespace
{
unsigned int constexpr WINDOW_WIDTH = 800;
unsigned int constexpr WINDOW_HEIGHT = 600;

void SubmitShaders(FIRE::MaterialFactory& materialFactory)
{
    materialFactory.CreateMaterialFromFiles("phong", "PhongVS.glsl", "PhongFS.glsl");
    materialFactory.CreateMaterialFromFiles("height", "HeightVS.glsl", "HeightFS.glsl");
    materialFactory.CreateMaterialFromFiles("grid", "GridVS.glsl", "GridFS.glsl");
}

void SetupScene(
    FIRE::Window& window,
    FIRE::Scene& scene,
    FIRE::Renderer& renderer,
    FIRE::MaterialFactory& materialFactory,
    FIRE::MeshManager& meshManager)
{
    auto input{std::make_shared<FIRE::InputListener>()};
    window.SetInputListener(input);

    auto& sponzaObj = scene.CreateSceneObject("sponza");
    std::vector<FIRE::Renderable> renderables;

    auto meshHandles = meshManager.CreateFromFile("sponza_mesh_", "sponza.obj");
    auto i = 0u;
    for(auto& handle : meshHandles)
    {
        std::stringstream ss;
        ss << "sponza_renderable_" << i++;
        renderables.emplace_back(ss.str(), materialFactory.GetMaterial("phong"), handle);
    }
    sponzaObj.AddComponent(std::make_unique<examples::Mesh3DRenderingComponent>(renderer, std::move(renderables)));

    auto& mainCamera = scene.CreateSceneObject("cam");
    mainCamera.AddComponent(
        std::make_unique<examples::InputMappingComponent>(mainCamera, *input, window, renderer));

    mainCamera.AddComponent(
        std::make_unique<examples::PerspectiveCameraComponent>(
            70.0f, static_cast<float>(window.GetWidth()) / static_cast<float>(window.GetHeight()), 0.1f, 3000.0f));

    auto& sceneLight = scene.CreateSceneObject("light");
    sceneLight.AddComponent(std::make_unique<examples::PointLightComponent>());

    auto& overlay = scene.CreateSceneObject("overlay");
    overlay.AddComponent(std::make_unique<examples::FPSOverlayComponent>(renderer));

    scene.Setup();
}

} // namespace

int main(int, char**)
{
    FIRE::Window window = FIRE::GLFactory::InitWindow("FIRE - cube", WINDOW_WIDTH, WINDOW_HEIGHT);

    FIRE::MeshManager meshManager;
    FIRE::MaterialFactory materialFactory(FIRE::GLFactory::CreateShaderFactory());
    SubmitShaders(materialFactory);

    auto renderer{FIRE::GLFactory::CreateRenderer()};

    FIRE::Scene scene;
    SetupScene(window, scene, *renderer, materialFactory, meshManager);

    FIRE::MainLoop(window, scene, *renderer);
}