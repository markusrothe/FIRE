#include <FIRE/Camera.h>
#include <FIRE/GLFactory.h>
#include <FIRE/InputListener.h>
#include <FIRE/RenderContext.h>
#include <FIRE/Renderable.h>
#include <FIRE/Renderer.h>
#include <FIRE/Scene.h>
#include <FIRE/Window.h>
#include <iostream>
#include <memory>
#include <sstream>

namespace
{
std::shared_ptr<FIRE::Renderable> CreateCube(std::string name)
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

    cubeMesh.GetVertexDeclaration().AddSection("vPos", 3u, 0, 0);

    auto cube = std::make_shared<FIRE::Renderable>(std::move(name));
    cube->SetMesh(std::move(cubeMesh));
    return cube;
}

std::shared_ptr<FIRE::Camera> CreateCamera()
{
    FIRE::Vector3 camPos{0, 0, 5};
    FIRE::Vector3 camViewDir{0.0f, 0.0f, -1.0f};
    return std::make_shared<FIRE::Camera>("cam", std::move(camPos), std::move(camViewDir));
}

} // namespace

int main(int, char**)
{
    FIRE::Window window{"example1", 800, 600};

    auto context{FIRE::GLFactory::CreateRenderContext(window)};
    window.SetRenderContext(std::move(context));

    auto input{std::make_shared<FIRE::InputListener>()};
    window.SetInputListener(input);

    auto cam = CreateCamera();

    FIRE::Scene scene;
    auto sceneComponent = scene.NewSceneComponent("sceneComponent");

    auto cube = CreateCube("cube");

    sceneComponent->AddRenderable(cube);
    auto renderer{FIRE::GLFactory::CreateRenderer()};
    auto const proj = FIRE::CreatePerspectiveMatrix(90.0f, 800.0f / 600.0f, 0.01f, 500.0f);

    auto moveRight = [cam] {
        auto& camTransform = cam->GetTransform();
        camTransform.Translate(camTransform.Right());
    };
    auto moveLeft = [cam] { auto& camTransform = cam->GetTransform(); camTransform.Translate(-camTransform.Right()); };
    auto moveUp = [cam] { auto& camTransform = cam->GetTransform(); camTransform.Translate(camTransform.Up()); };
    auto moveDown = [cam] { auto& camTransform = cam->GetTransform(); camTransform.Translate(-camTransform.Up()); };
    auto moveForward = [cam] { auto& camTransform = cam->GetTransform(); camTransform.Translate(camTransform.Orientation()); };
    auto moveBackward = [cam] { auto& camTransform = cam->GetTransform(); camTransform.Translate(-camTransform.Orientation()); };

    input->Register(FIRE::Key::KEY_D, FIRE::KeyAction::PRESS, moveRight);
    input->Register(FIRE::Key::KEY_D, FIRE::KeyAction::REPEAT, moveRight);
    input->Register(FIRE::Key::KEY_A, FIRE::KeyAction::PRESS, moveLeft);
    input->Register(FIRE::Key::KEY_A, FIRE::KeyAction::REPEAT, moveLeft);
    input->Register(FIRE::Key::KEY_Q, FIRE::KeyAction::PRESS, moveUp);
    input->Register(FIRE::Key::KEY_Q, FIRE::KeyAction::REPEAT, moveUp);
    input->Register(FIRE::Key::KEY_E, FIRE::KeyAction::PRESS, moveDown);
    input->Register(FIRE::Key::KEY_E, FIRE::KeyAction::REPEAT, moveDown);
    input->Register(FIRE::Key::KEY_W, FIRE::KeyAction::PRESS, moveForward);
    input->Register(FIRE::Key::KEY_W, FIRE::KeyAction::REPEAT, moveForward);
    input->Register(FIRE::Key::KEY_S, FIRE::KeyAction::PRESS, moveBackward);
    input->Register(FIRE::Key::KEY_S, FIRE::KeyAction::REPEAT, moveBackward);

    while(!window.ShouldClose())
    {
        window.PollEvents();

        cube->GetTransform().Rotate(FIRE::Vector3(1, 1, 1), 1.0f);
        cube->SetShaderUniformMat4x4("MVP", proj * cam->ViewMatrix() * cube->GetTransform().ModelMatrix());

        renderer->Render(scene);
        window.SwapBuffers();
    }
}
