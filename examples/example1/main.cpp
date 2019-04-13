#include <FIRE/Camera.h>
#include <FIRE/GLFactory.h>
#include <FIRE/RenderContext.h>
#include <FIRE/Renderable.h>
#include <FIRE/Renderer.h>
#include <FIRE/Window.h>

int main(int, char**)
{
    FIRE::Window window{"example1", 800, 600};

    auto context{FIRE::GLFactory::CreateRenderContext(window)};
    window.SetRenderContext(std::move(context));

    FIRE::Mesh cubeMesh{"cubeMesh"};

    cubeMesh.AddVertices({
        {-1.0f, -1.0f, 1.0f},
        {1.0f, -1.0f, 1.0f},
        {1.0f, -1.0f, -1.0f},
        {-1.0f, -1.0f, -1.0f},
        {-1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, -1.0f},
        {-1.0f, 1.0f, -1.0f}
    });

    cubeMesh.AddIndices({0, 1, 5, 0, 5, 4,
                         1, 2, 6, 1, 6, 5,
                         2, 3, 7, 2, 7, 6,
                         3, 0, 4, 3, 4, 7,
                         4, 5, 6, 4, 6, 7,
                         2, 3, 1, 2, 1, 0});

    cubeMesh.GetVertexDeclaration().AddSection("vPos", 3u, 0, 0);

    FIRE::Renderable cube{"cube"};
    cube.SetMesh(std::move(cubeMesh));

    FIRE::Vertex camPos{1.5f, 2, 2};
    FIRE::Vertex camLookAt{0, 0, 0};
    FIRE::Camera cam{"cam", std::move(camPos), std::move(camLookAt)};

    cube.SetShaderUniformMat4x4("MVP", FIRE::CreatePerspectiveMatrix(90.0f, 800.0f / 600.0f, 0.01f, 20.0f) * cam.ViewMatrix());

    auto renderer{FIRE::GLFactory::CreateRenderer()};

    while(!window.ShouldClose())
    {
        window.PollEvents();

        renderer->Render(cube);

        window.SwapBuffers();
    }
}
