#include <FIRE/Camera.h>
#include <FIRE/GLFactory.h>
#include <FIRE/InputListener.h>
#include <FIRE/MaterialFactory.h>
#include <FIRE/MeshFactory.h>
#include <FIRE/RenderContext.h>
#include <FIRE/Renderable.h>
#include <FIRE/Renderer.h>
#include <FIRE/Scene.h>
#include <FIRE/ShaderFactory.h>
#include <FIRE/Window.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <streambuf>

namespace
{
unsigned int constexpr WINDOW_WIDTH = 800;
unsigned int constexpr WINDOW_HEIGHT = 600;
FIRE::Vector3 const lightPos(5.0f, 10.0f, 7.0f);

std::string GetFileContent(std::string const& filePath)
{
    std::ifstream file(filePath);
    std::string const content{(std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()};
    return content;
}

std::unique_ptr<FIRE::Renderable> CreateRenderable(std::string&& name, std::shared_ptr<FIRE::Mesh> const& mesh, FIRE::Material const& material)
{
    auto renderable = std::make_unique<FIRE::Renderable>(std::move(name));
    renderable->SetMesh(mesh);
    renderable->SetMaterial(material);
    return renderable;
}

std::shared_ptr<FIRE::Renderable> CreatePlane(std::string&& name, FIRE::Material const& material)
{
    FIRE::MeshFactory factory;
    auto planeMesh = factory.CreatePlane("plane");
    planeMesh->GetVertexDeclaration().AddSection("vPos", 3u, 0u);
    planeMesh->GetVertexDeclaration().AddSection("vNormal", 3u, planeMesh->Positions().size() * sizeof(float) * 3);
    return CreateRenderable(std::move(name), planeMesh, material);
}

std::shared_ptr<FIRE::Renderable> CreateCube(std::string&& name, FIRE::Material const& material)
{
    FIRE::MeshFactory factory;
    auto cubeMesh = factory.CreateCube("cube");
    cubeMesh->GetVertexDeclaration().AddSection("vPos", 3u, 0u);
    cubeMesh->GetVertexDeclaration().AddSection("vNormal", 3u, cubeMesh->Positions().size() * sizeof(float) * 3);
    return CreateRenderable(std::move(name), cubeMesh, material);
}

std::shared_ptr<FIRE::Renderable> CreateSphere(std::string&& name, FIRE::Material const& material)
{
    FIRE::MeshFactory factory;
    auto sphereMesh = factory.CreateSphere("sphere", 20);
    sphereMesh->GetVertexDeclaration().AddSection("vPos", 3u, 0u);
    sphereMesh->GetVertexDeclaration().AddSection("vNormal", 3u, sphereMesh->Positions().size() * sizeof(float) * 3);
    return CreateRenderable(std::move(name), sphereMesh, material);
}

std::shared_ptr<FIRE::Camera> CreateCamera()
{
    FIRE::Vector3 camPos{0, 2, 10};
    FIRE::Vector3 lookAt{0.0f, 2.0f, 0.0f};
    return std::make_shared<FIRE::Camera>("cam", std::move(camPos), std::move(lookAt));
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

void MapInput(std::shared_ptr<FIRE::Camera> const& cam, FIRE::Window& window)
{
    auto input{std::make_shared<FIRE::InputListener>()};
    window.SetInputListener(input);

    auto moveRight = [cam] { auto& camTransform = cam->GetTransform(); camTransform.Translate(camTransform.Right()); };
    input->RegisterKeyEvent(FIRE::Key::KEY_D, FIRE::KeyAction::PRESS, moveRight);
    input->RegisterKeyEvent(FIRE::Key::KEY_D, FIRE::KeyAction::REPEAT, moveRight);

    auto moveLeft = [cam] { auto& camTransform = cam->GetTransform(); camTransform.Translate(-camTransform.Right()); };
    input->RegisterKeyEvent(FIRE::Key::KEY_A, FIRE::KeyAction::PRESS, moveLeft);
    input->RegisterKeyEvent(FIRE::Key::KEY_A, FIRE::KeyAction::REPEAT, moveLeft);

    auto moveUp = [cam] { auto& camTransform = cam->GetTransform(); camTransform.Translate(camTransform.Up()); };
    input->RegisterKeyEvent(FIRE::Key::KEY_Q, FIRE::KeyAction::PRESS, moveUp);
    input->RegisterKeyEvent(FIRE::Key::KEY_Q, FIRE::KeyAction::REPEAT, moveUp);

    auto moveDown = [cam] { auto& camTransform = cam->GetTransform(); camTransform.Translate(-camTransform.Up()); };
    input->RegisterKeyEvent(FIRE::Key::KEY_E, FIRE::KeyAction::PRESS, moveDown);
    input->RegisterKeyEvent(FIRE::Key::KEY_E, FIRE::KeyAction::REPEAT, moveDown);

    auto moveForward = [cam] { auto& camTransform = cam->GetTransform(); camTransform.Translate(camTransform.LookAt() - camTransform.Position()); };
    input->RegisterKeyEvent(FIRE::Key::KEY_W, FIRE::KeyAction::PRESS, moveForward);
    input->RegisterKeyEvent(FIRE::Key::KEY_W, FIRE::KeyAction::REPEAT, moveForward);

    auto moveBackward = [cam] { auto& camTransform = cam->GetTransform(); camTransform.Translate(-(camTransform.LookAt() - camTransform.Position())); };
    input->RegisterKeyEvent(FIRE::Key::KEY_S, FIRE::KeyAction::PRESS, moveBackward);
    input->RegisterKeyEvent(FIRE::Key::KEY_S, FIRE::KeyAction::REPEAT, moveBackward);

    auto closeWindow = [&window] { window.Close(); };
    input->RegisterKeyEvent(FIRE::Key::KEY_ESC, FIRE::KeyAction::PRESS, closeWindow);

    input->RegisterMouseButtonEvent(
        FIRE::MouseKey::LEFT_BUTTON, FIRE::KeyAction::PRESS, [cam, input, &window] {
            window.CaptureCursor();

            bool firstCallback = true;
            auto rotate = [cam, firstCallback = std::move(firstCallback)](double x, double y) mutable {
                static double oldX = 0;
                static double oldY = 0;

                if(!firstCallback)
                {
                    auto const deltaX = x - oldX;
                    auto const deltaY = y - oldY;
                    auto& camTransform = cam->GetTransform();
                    camTransform.Rotate(camTransform.Up(), static_cast<float>(-deltaX) / 10.0f);    // around up-axis
                    camTransform.Rotate(camTransform.Right(), static_cast<float>(-deltaY) / 10.0f); // around right-axis
                }
                else
                {
                    firstCallback = false;
                }
                oldX = x;
                oldY = y;
            };

            input->RegisterMouseEvent(rotate);
        });

    input->RegisterMouseButtonEvent(
        FIRE::MouseKey::LEFT_BUTTON, FIRE::KeyAction::RELEASE, [input, &window] {
            input->UnregisterMouseEvent();
            window.ReleaseCursor();
        });
}

} // namespace

int main(int, char**)
{
    FIRE::Window window{"FIRE cube example", WINDOW_WIDTH, WINDOW_HEIGHT};
    auto context{FIRE::GLFactory::CreateRenderContext(window)};
    window.SetRenderContext(std::move(context));

    auto cam = CreateCamera();
    MapInput(cam, window);

    auto const material = CreatePhongMaterial();
    auto cube = CreateCube("cube", material);
    cube->GetTransform().Translate(0.0f, 4.0f, 0.0f);
    cube->GetMaterial().SetShaderParameter("LightPos", FIRE::ShaderParameterType::VEC3, lightPos);

    auto plane = CreatePlane("plane", material);
    plane->GetTransform().Scale(FIRE::Vector3(20.0f, 1.0f, 20.0f));
    plane->GetMaterial().SetShaderParameter("LightPos", FIRE::ShaderParameterType::VEC3, lightPos);

    auto const defaultMaterial = CreateDefaultMaterial();
    auto sphere = CreateSphere("sphere", material);
    sphere->GetMaterial().SetShaderParameter("LightPos", FIRE::ShaderParameterType::VEC3, lightPos);

    auto lightCube = CreateCube("cube", defaultMaterial);
    lightCube->GetTransform().Translate(lightPos);
    lightCube->GetTransform().Scale(FIRE::Vector3(0.1f, 0.1f, 0.1f));
    lightCube->GetMaterial().SetShaderParameter("LightPos", FIRE::ShaderParameterType::VEC3, lightPos);

    auto const proj = FIRE::CreatePerspectiveMatrix(70.0f, static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT), 0.01f, 500.0f);

    FIRE::Scene scene;
    auto sceneComponent = scene.NewSceneComponent("sceneComponent");
    sceneComponent->AddRenderable(cube);
    sceneComponent->AddRenderable(plane);
    sceneComponent->AddRenderable(lightCube);
    sceneComponent->AddRenderable(sphere);

    auto renderer{FIRE::GLFactory::CreateRenderer()};
    while(!window.ShouldClose())
    {
        window.PollEvents();

        cube->GetTransform().Rotate(FIRE::Vector3(1, 1, 1), 1.0f);

        auto VP = proj * cam->ViewMatrix();
        cube->GetMaterial().SetShaderParameter("M", FIRE::ShaderParameterType::MAT4x4, cube->GetTransform().ModelMatrix());
        cube->GetMaterial().SetShaderParameter("VP", FIRE::ShaderParameterType::MAT4x4, VP);

        plane->GetMaterial().SetShaderParameter("M", FIRE::ShaderParameterType::MAT4x4, plane->GetTransform().ModelMatrix());
        plane->GetMaterial().SetShaderParameter("VP", FIRE::ShaderParameterType::MAT4x4, VP);

        sphere->GetMaterial().SetShaderParameter("M", FIRE::ShaderParameterType::MAT4x4, sphere->GetTransform().ModelMatrix());
        sphere->GetMaterial().SetShaderParameter("VP", FIRE::ShaderParameterType::MAT4x4, VP);

        lightCube->GetMaterial().SetShaderParameter("MVP", FIRE::ShaderParameterType::MAT4x4, VP * lightCube->GetTransform().ModelMatrix());

        renderer->Render(scene);
        window.SwapBuffers();
    }
}
