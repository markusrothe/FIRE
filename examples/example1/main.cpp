#include <FIRE/Camera.h>
#include <FIRE/GLFactory.h>
#include <FIRE/RenderContext.h>
#include <FIRE/Renderable.h>
#include <FIRE/Renderer.h>
#include <FIRE/Scene.h>
#include <FIRE/Window.h>
#include <memory>

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
                         2, 3, 1, 2, 1, 0});

    cubeMesh.GetVertexDeclaration().AddSection("vPos", 3u, 0, 0);

    auto cube = std::make_shared<FIRE::Renderable>(std::move(name));
    cube->SetMesh(std::move(cubeMesh));
    return cube;
}

std::shared_ptr<FIRE::Camera> CreateCamera()
{
    FIRE::Vector3 camPos{10, 10, 10};
    FIRE::Vector3 camLookAt{0, 1, 0};
    return std::make_shared<FIRE::Camera>("cam", std::move(camPos), std::move(camLookAt));
}
} // namespace

int main(int, char**)
{
    FIRE::Window window{"example1", 800, 600};

    auto context{FIRE::GLFactory::CreateRenderContext(window)};
    window.SetRenderContext(std::move(context));

    auto cam = CreateCamera();

    auto cube = CreateCube("cube1");
    auto cube2 = CreateCube("cube2");

    FIRE::Matrix4x4 viewMatrix = cam->ViewMatrix();
    FIRE::Matrix4x4 projMatrix = FIRE::CreatePerspectiveMatrix(90.0f, 800.0f / 600.0f, 1.f, 20.0f);
    FIRE::Matrix4x4 modelMatrix;
    modelMatrix.At(3, 0) = 4;
    modelMatrix.At(3, 1) = 7;
    modelMatrix.At(3, 2) = 10;

    auto mat0 = projMatrix * viewMatrix;
    cube->SetShaderUniformMat4x4("MVP", mat0);

    FIRE::Scene scene;
    auto sceneComponent = scene.NewSceneComponent("sceneComponent");
    sceneComponent->AddRenderable(cube);

    cube2->SetShaderUniformMat4x4("MVP", projMatrix * viewMatrix * modelMatrix);
    sceneComponent->AddRenderable(cube2);

    auto renderer{FIRE::GLFactory::CreateRenderer()};

    while(!window.ShouldClose())
    {
        cube2->SetShaderUniformMat4x4("MVP", projMatrix * viewMatrix * modelMatrix);
        window.PollEvents();
        renderer->Render(scene);
        window.SwapBuffers();
    }
}
