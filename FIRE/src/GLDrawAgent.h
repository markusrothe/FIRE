#ifndef FIRE_GLDrawAgent_h
#define FIRE_GLDrawAgent_h
#include "DrawAgent.h"
#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <memory>
namespace FIRE
{
class MeshManager;
class GLDrawAgent : public DrawAgent
{
public:
    explicit GLDrawAgent(MeshManager& meshFactory);
    void Clear() override;

    void Draw(Renderable const& renderable, GLVertexArrayObject arrObj) override;

private:
    MeshManager& m_meshManager;
};
} // namespace FIRE

#endif // !FIRE_GLDrawAgent_h
