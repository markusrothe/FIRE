#include <FIRE/Camera.h>
#include <FIRE/GLFactory.h>
#include <FIRE/RenderContext.h>
#include <FIRE/Renderable.h>
#include <FIRE/Renderer.h>
#include <FIRE/Scene.h>
#include <FIRE/Window.h>
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
                         2, 3, 1, 2, 1, 0});

    cubeMesh.GetVertexDeclaration().AddSection("vPos", 3u, 0, 0);

    auto cube = std::make_shared<FIRE::Renderable>(std::move(name));
    cube->SetMesh(std::move(cubeMesh));
    return cube;
}

std::shared_ptr<FIRE::Camera> CreateCamera()
{
    FIRE::Vector3 camPos{0.1, 5, 0};
    FIRE::Vector3 camLookAt{0, 0, 0};
    return std::make_shared<FIRE::Camera>("cam", std::move(camPos), std::move(camLookAt));
}

} // namespace

int main(int, char**)
{
    FIRE::Window window{"example1", 800, 600};

    auto context{FIRE::GLFactory::CreateRenderContext(window)};
    window.SetRenderContext(std::move(context));

    auto cam = CreateCamera();

    FIRE::Scene scene;
    auto sceneComponent = scene.NewSceneComponent("sceneComponent");

    auto cube = CreateCube("cube");
    auto cube2 = CreateCube("2ndCube");

    sceneComponent->AddRenderable(cube);
    sceneComponent->AddRenderable(cube2);
    cube2->GetTransform().Translate(5, 0, 0);
    auto renderer{FIRE::GLFactory::CreateRenderer()};

    FIRE::Transform transform;
    auto const proj = FIRE::CreatePerspectiveMatrix(90.0f, 800.0f / 600.0f, 0.01f, 500.0f);
    auto const view = cam->ViewMatrix();

    while(!window.ShouldClose())
    {
        window.PollEvents();

        transform.Rotate(FIRE::Vector3(0, 1, 0), 1.0f);
        cube->SetShaderUniformMat4x4("MVP", proj * view * cube->GetTransform().ModelMatrix());
        cube2->SetShaderUniformMat4x4("MVP", proj * view * transform.ModelMatrix() * cube2->GetTransform().ModelMatrix());

        renderer->Render(scene);
        window.SwapBuffers();
    }
}
