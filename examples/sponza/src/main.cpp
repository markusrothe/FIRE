
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
#include <FIRE/ModelLoader.h>
#include <FIRE/RenderContext.h>
#include <FIRE/Renderer.h>
#include <FIRE/Scene.h>
#include <FIRE/TextureManager.h>
#include <FIRE/Window.h>

#include <memory>
#include <sstream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>
namespace
{
unsigned int constexpr WINDOW_WIDTH = 1920;
unsigned int constexpr WINDOW_HEIGHT = 1080;

void SubmitShaders(FIRE::MaterialFactory& materialFactory)
{
    materialFactory.CreateMaterialFromFiles("phong", "PhongVS.glsl", "PhongFS.glsl");
    materialFactory.CreateMaterialFromFiles("height", "HeightVS.glsl", "HeightFS.glsl");
    materialFactory.CreateMaterialFromFiles("grid", "GridVS.glsl", "GridFS.glsl");
    materialFactory.CreateMaterialFromFiles("texCoords", "texCoordsVS.glsl", "texCoordsFS.glsl");
    materialFactory.CreateMaterialFromFiles("texSampling", "textureSamplingVS.glsl", "textureSamplingFS.glsl");
    materialFactory.CreateMaterialFromFiles("text", "textVS.glsl", "textFS.glsl");
}

std::vector<FIRE::Renderable> LoadSponzaModel(FIRE::MeshManager& meshManager, FIRE::MaterialFactory& materialFactory, FIRE::TextureManager& texManager)
{
    std::vector<FIRE::Renderable> renderables;
    FIRE::ModelLoader loader(FIRE::ModelLoader::Source::File, "sponza.obj");

    renderables.reserve(loader.GetNumModels());
    auto numModels = loader.GetNumModels();
    for(auto i = 0u; i < numModels; ++i)
    {
        FIRE::Renderable renderable;
        auto model = loader.StealModel(0u);
        renderable.mesh = meshManager.AddMesh(std::move(model.mesh));
        renderable.name = "renderable_" + renderable.mesh->Name();
        renderable.material = materialFactory.GetMaterial("texSampling");
        // ... process data if not NULL ...
        // ... x = width, y = height, n = # 8-bit components per pixel ...
        // ... replace '0' with '1'..'4' to force that many components per pixel
        // ... but 'n' will always be the number that it would have been if you said 0
        std::string fullPath{std::string("./") + model.texturePath};
        int width, height, numComponents;
        unsigned char* data = stbi_load(fullPath.c_str(), &width, &height, &numComponents, 0);
        if(data)
        {
            std::vector<uint8_t> pixels(data, data + (height * width * numComponents));
            stbi_image_free(data);
            auto const texName = model.texturePath;
            auto tex = texManager.CreateImageTexture(texName, width, height, pixels, static_cast<uint8_t>(numComponents), model.textureWrapping, FIRE::Texture2D::Filter::LINEAR);
            renderable.material.AddTexture(tex, 0u);
        }
        renderables.push_back(renderable);
    }

    return renderables;
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

    auto& sponzaObj = scene.CreateSceneObject("sponza");

    auto renderables = LoadSponzaModel(meshManager, materialFactory, texManager);

    sponzaObj.AddComponent(std::make_unique<examples::Mesh3DRenderingComponent>(renderer, std::move(renderables)));

    auto& mainCamera = scene.CreateSceneObject("cam");
    mainCamera.AddComponent(std::make_unique<examples::InputMappingComponent>(mainCamera, *input, window, renderer));
    mainCamera.AddComponent(std::make_unique<examples::PerspectiveCameraComponent>(
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
