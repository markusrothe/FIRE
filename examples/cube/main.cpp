#include <FIRE/Camera.h>
#include <FIRE/GLFactory.h>
#include <FIRE/InputListener.h>
#include <FIRE/MaterialFactory.h>
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

std::string GetFileContent(std::string const& filePath)
{
    std::ifstream file(filePath);
    std::string const content{(std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()};
    return content;
}

FIRE::Mesh CreatePlaneMesh()
{
    FIRE::Mesh planeMesh{"planeMesh"};

    planeMesh.AddVertices({{-100.0f, 0.0f, -100.0f},
                           {-100.0f, 0.0f, 100.0f},
                           {100.0f, 0.0f, 100.0f},
                           {100.0f, 0.0f, -100.0f}});

    planeMesh.AddNormals({{0.0f, 1.0f, 0.0f},
                          {0.0f, 1.0f, 0.0f},
                          {0.0f, 1.0f, 0.0f},
                          {0.0f, 1.0f, 0.0f}});

    planeMesh.AddIndices({0, 1, 2, 0, 2, 3});
    return planeMesh;
}

FIRE::Mesh CreateCubeMesh()
{
    FIRE::Mesh cubeMesh{"cubeMesh"};
    cubeMesh.AddVertices({{-1.0f, -1.0f, 1.0f},
                          {1.0f, -1.0f, 1.0f},
                          {1.0f, -1.0f, -1.0f},
                          {-1.0f, -1.0f, -1.0f},
                          {-1.0f, 1.0f, 1.0f},
                          {1.0f, 1.0f, 1.0f},
                          {1.0f, 1.0f, -1.0f},
                          {-1.0f, 1.0f, -1.0f}});

    cubeMesh.AddIndices({0, 1, 5, 0, 5, 4,
                         1, 2, 6, 1, 6, 5,
                         2, 3, 7, 2, 7, 6,
                         3, 0, 4, 3, 4, 7,
                         4, 5, 6, 4, 6, 7,
                         2, 1, 3, 3, 1, 0});
    return cubeMesh;
}

std::unique_ptr<FIRE::Renderable> CreateRenderable(std::string&& name, FIRE::Mesh&& mesh, FIRE::Material&& material)
{
    auto renderable = std::make_unique<FIRE::Renderable>(std::move(name));
    renderable->SetMesh(std::move(mesh));
    renderable->SetMaterial(std::move(material));
    return renderable;
}

std::shared_ptr<FIRE::Renderable> CreatePlane(std::string&& name, FIRE::ShaderFactory& shaderFactory)
{
    FIRE::Mesh planeMesh = CreatePlaneMesh();
    planeMesh.GetVertexDeclaration().AddSection("vPos", 3u, 0, 0);
    planeMesh.GetVertexDeclaration().AddSection("vNormal", 3u, static_cast<unsigned int>(planeMesh.Vertices().size() * 3 * sizeof(float)), 0);

    FIRE::Shaders const shaders = {
        {FIRE::ShaderType::VERTEX_SHADER, GetFileContent("PhongVS.glsl")},
        {FIRE::ShaderType::FRAGMENT_SHADER, GetFileContent("PhongFS.glsl")}};

    return CreateRenderable(std::move(name), std::move(planeMesh), FIRE::MaterialFactory::Create("phong", shaders, shaderFactory));
}

std::shared_ptr<FIRE::Renderable> CreateCube(std::string&& name, FIRE::ShaderFactory& shaderFactory)
{
    auto cubeMesh = CreateCubeMesh();
    cubeMesh.GetVertexDeclaration().AddSection("vPos", 3u, 0, 0);

    return CreateRenderable(std::move(name), std::move(cubeMesh), FIRE::MaterialFactory::CreateDefault(shaderFactory));
}

std::shared_ptr<FIRE::Camera> CreateCamera()
{
    FIRE::Vector3 camPos{0, 2, 10};
    FIRE::Vector3 lookAt{0.0f, 2.0f, 0.0f};
    return std::make_shared<FIRE::Camera>("cam", std::move(camPos), std::move(lookAt));
}

void MapInput(std::shared_ptr<FIRE::Camera> const& cam, FIRE::Window& window)
{
    auto input{std::make_shared<FIRE::InputListener>()};
    window.SetInputListener(input);

    auto closeWindow = [&window] { window.Close(); };

    auto moveRight = [cam] { auto& camTransform = cam->GetTransform(); camTransform.Translate(camTransform.Right()); };
    auto moveLeft = [cam] { auto& camTransform = cam->GetTransform(); camTransform.Translate(-camTransform.Right()); };
    auto moveUp = [cam] { auto& camTransform = cam->GetTransform(); camTransform.Translate(camTransform.Up()); };
    auto moveDown = [cam] { auto& camTransform = cam->GetTransform(); camTransform.Translate(-camTransform.Up()); };
    auto moveForward = [cam] { auto& camTransform = cam->GetTransform(); camTransform.Translate(camTransform.LookAt() - camTransform.Position()); };
    auto moveBackward = [cam] { auto& camTransform = cam->GetTransform(); camTransform.Translate(-(camTransform.LookAt() - camTransform.Position())); };

    input->RegisterKeyEvent(FIRE::Key::KEY_D, FIRE::KeyAction::PRESS, moveRight);
    input->RegisterKeyEvent(FIRE::Key::KEY_D, FIRE::KeyAction::REPEAT, moveRight);
    input->RegisterKeyEvent(FIRE::Key::KEY_A, FIRE::KeyAction::PRESS, moveLeft);
    input->RegisterKeyEvent(FIRE::Key::KEY_A, FIRE::KeyAction::REPEAT, moveLeft);
    input->RegisterKeyEvent(FIRE::Key::KEY_Q, FIRE::KeyAction::PRESS, moveUp);
    input->RegisterKeyEvent(FIRE::Key::KEY_Q, FIRE::KeyAction::REPEAT, moveUp);
    input->RegisterKeyEvent(FIRE::Key::KEY_E, FIRE::KeyAction::PRESS, moveDown);
    input->RegisterKeyEvent(FIRE::Key::KEY_E, FIRE::KeyAction::REPEAT, moveDown);
    input->RegisterKeyEvent(FIRE::Key::KEY_W, FIRE::KeyAction::PRESS, moveForward);
    input->RegisterKeyEvent(FIRE::Key::KEY_W, FIRE::KeyAction::REPEAT, moveForward);
    input->RegisterKeyEvent(FIRE::Key::KEY_S, FIRE::KeyAction::PRESS, moveBackward);
    input->RegisterKeyEvent(FIRE::Key::KEY_S, FIRE::KeyAction::REPEAT, moveBackward);
    input->RegisterKeyEvent(FIRE::Key::KEY_ESC, FIRE::KeyAction::PRESS, closeWindow);

    double oldX = 0, oldY = 0;
    auto firstCallback = true;
    auto rotate = [cam, oldX = std::move(oldX), oldY = std::move(oldY), firstCallback = std::move(firstCallback)](double x, double y) mutable {
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
            // Only initialize x and y the first time that this callback is called and do no camera rotation to prevent camera jumps
            firstCallback = false;
        }
        oldX = x;
        oldY = y;
    };
    input->RegisterMouseEvent(rotate);
    input->RegisterMouseButtonEvent(FIRE::MouseKey::LEFT_BUTTON, FIRE::KeyAction::PRESS, closeWindow);
}

} // namespace

int main(int, char**)
{
    FIRE::Window window{"FIRE cube example", WINDOW_WIDTH, WINDOW_HEIGHT};

    auto context{FIRE::GLFactory::CreateRenderContext(window)};
    window.SetRenderContext(std::move(context));

    auto cam = CreateCamera();

    MapInput(cam, window);

    FIRE::Scene scene;
    auto sceneComponent = scene.NewSceneComponent("sceneComponent");

    auto shaderFactory{FIRE::GLFactory::CreateShaderFactory()};
    auto cube = CreateCube("cube", *shaderFactory);
    cube->GetTransform().Translate(0.0f, 2.0f, 0.0f);
    auto plane = CreatePlane("plane", *shaderFactory);

    sceneComponent->AddRenderable(cube);
    sceneComponent->AddRenderable(plane);

    auto const fovy = 70.0f;
    auto const near = 0.01f;
    auto const far = 500.0f;
    auto const proj = FIRE::CreatePerspectiveMatrix(fovy, static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT), near, far);

    auto renderer{FIRE::GLFactory::CreateRenderer()};
    FIRE::Vector3 const lightPos(0.0f, 10.0f, 0.0f);
    while(!window.ShouldClose())
    {
        window.PollEvents();

        cube->GetTransform().Rotate(FIRE::Vector3(1, 1, 1), 10.0f);
        cube->GetMaterial().SetShaderParameter("MVP", FIRE::ShaderParameterType::MAT4x4, proj * cam->ViewMatrix() * cube->GetTransform().ModelMatrix());
        plane->GetMaterial().SetShaderParameter("MVP", FIRE::ShaderParameterType::MAT4x4, proj * cam->ViewMatrix() * plane->GetTransform().ModelMatrix());
        plane->GetMaterial().SetShaderParameter("LightPos", FIRE::ShaderParameterType::VEC3, lightPos);

        renderer->Render(scene);
        window.SwapBuffers();
    }
}
