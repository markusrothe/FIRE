#include "GLDraw.h"
#include "VertexLayout.h"
#include <FIRE/Mesh3D.h>
#include <glad/glad.h>
#include <iostream>
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
void message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei, GLchar const* message, void const*)
{
    auto const src_str = [source]() {
        switch(source)
        {
        case GL_DEBUG_SOURCE_API:
            return "API";
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            return "WINDOW SYSTEM";
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            return "SHADER COMPILER";
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            return "THIRD PARTY";
        case GL_DEBUG_SOURCE_APPLICATION:
            return "APPLICATION";
        case GL_DEBUG_SOURCE_OTHER:
            return "OTHER";
        default:
            assert(false);
            return "";
        }
    }();

    auto const type_str = [type]() {
        switch(type)
        {
        case GL_DEBUG_TYPE_ERROR:
            return "ERROR";
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            return "DEPRECATED_BEHAVIOR";
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            return "UNDEFINED_BEHAVIOR";
        case GL_DEBUG_TYPE_PORTABILITY:
            return "PORTABILITY";
        case GL_DEBUG_TYPE_PERFORMANCE:
            return "PERFORMANCE";
        case GL_DEBUG_TYPE_MARKER:
            return "MARKER";
        case GL_DEBUG_TYPE_OTHER:
            return "OTHER";
        default:
            assert(false);
            return "";
        }
    }();

    auto const severity_str = [severity]() {
        switch(severity)
        {
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            return "NOTIFICATION";
        case GL_DEBUG_SEVERITY_LOW:
            return "LOW";
        case GL_DEBUG_SEVERITY_MEDIUM:
            return "MEDIUM";
        case GL_DEBUG_SEVERITY_HIGH:
            return "HIGH";
        default:
            assert(false);
            return "";
        }
    }();

    std::cout << src_str << ", " << type_str << ", " << severity_str << ", " << id << ": " << message << '\n';
}
} // namespace

GLDraw::GLDraw()
{
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(
        [](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
            message_callback(source, type, id, severity, length, message, userParam);
        },
        nullptr);
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
void GLDraw::DoDraw(VertexLayout& layout, MeshPrimitives primitives, uint32_t count)
{
    layout.BindLayout();
    glDrawArrays(MapPrimitiveType(primitives), 0, static_cast<GLsizei>(count));
    layout.ReleaseLayout();
}

void GLDraw::DoDrawIndexed(VertexLayout& layout, MeshPrimitives primitives, uint32_t count)
{
    layout.BindLayout();
    glDrawElements(MapPrimitiveType(primitives), static_cast<GLsizei>(count), GL_UNSIGNED_INT, nullptr);
    layout.ReleaseLayout();
}

} // namespace FIRE
