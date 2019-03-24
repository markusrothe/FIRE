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

    FIRE::Mesh triangleMesh{"triangleMesh"};
    triangleMesh.AddVertices(
        {{-1.0f, -1.0f, 0.0f}, {1.0f, -1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}});
    triangleMesh.AddIndices({0, 1, 2});
    triangleMesh.GetVertexDeclaration().AddSection("vPos", 3u, 0, 0);

    FIRE::Renderable triangle{"triangle"};
    triangle.SetMesh(std::move(triangleMesh));

    auto renderer{FIRE::GLFactory::CreateRenderer()};

    while(!window.ShouldClose())
    {
        window.PollEvents();

        renderer->Render(triangle);

        window.SwapBuffers();
    }
}
