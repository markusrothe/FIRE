#include "GLDraw.h"
#include <FIRE/Mesh3D.h>
#include <glad/glad.h>
namespace FIRE
{
namespace
{
GLenum MapPrimitiveType(MeshPrimitives primitives)
{
    switch(primitives)
    {
    case MeshPrimitives::Points:
        return GL_POINTS;
    case MeshPrimitives::Lines:
        return GL_LINES;
    case MeshPrimitives::Triangles:
        return GL_TRIANGLES;
    default:
        assert(false);
        return GL_POINTS;
    }
}
} // namespace

GLDraw::GLDraw()
{
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
}

void GLDraw::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLDraw::ToggleWireframe()
{
    static bool on = true;
    glPolygonMode(GL_FRONT_AND_BACK, on ? GL_LINE : GL_FILL);
    on = !on;
}
void GLDraw::DoDraw(Mesh3D* mesh)
{
    glDrawElements(MapPrimitiveType(mesh->GetMeshType().primitives), static_cast<GLsizei>(mesh->Indices().size()), GL_UNSIGNED_INT, 0);
}

} // namespace FIRE
