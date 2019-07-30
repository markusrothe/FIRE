#ifndef FIRE_STATICGEOMETRYRENDERER_H
#define FIRE_STATICGEOMETRYRENDERER_H

#include "GLBuffer.h"
#include <glad/glad.h>
#include <unordered_map>

namespace FIRE
{
class MeshManager;
struct Renderable;

class StaticGeometryRenderer
{
public:
    explicit StaticGeometryRenderer(MeshManager& meshManager);

    void Render(Renderable const& renderable);

private:
    GLVertexArrayObject Upload(Renderable const& renderable);
    void Draw(Renderable const& renderable, GLVertexArrayObject vertexArrayObject);

    MeshManager& m_meshManager;
    std::unordered_map<std::string, GLVertexArrayObject> m_uploadedRenderables{};
};
} // namespace FIRE
#endif //FIRE_STATICGEOMETRYRENDERER_H
