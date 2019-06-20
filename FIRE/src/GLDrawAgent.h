#ifndef FIRE_GLDrawAgent_h
#define FIRE_GLDrawAgent_h
#include "DrawAgent.h"
#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <memory>
namespace FIRE
{
class GLDrawAgent : public DrawAgent
{
public:
    GLDrawAgent();
    void Clear() override;

    void Draw(Renderable const& renderable, GLVertexArrayObject arrObj) override;
};
} // namespace FIRE

#endif // !FIRE_GLDrawAgent_h
