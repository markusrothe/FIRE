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

    void Draw(
        Renderable const& renderable,
        std::tuple<GLuint, GLuint, GLuint> buffers) override;
};
} // namespace FIRE

#endif // !FIRE_GLDrawAgent_h
