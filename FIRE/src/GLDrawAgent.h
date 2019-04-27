#ifndef FIRE_GLDrawAgent_h
#define FIRE_GLDrawAgent_h
#include "DrawAgent.h"
#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <memory>
namespace FIRE
{
class MaterialManager;
class GLDrawAgent : public DrawAgent
{
public:
    explicit GLDrawAgent(std::shared_ptr<MaterialManager> materialManager);
    void Clear() override;
    void Draw(
        Renderable const& renderable,
        std::tuple<GLuint, GLuint, GLuint> buffers) override;

private:
    std::shared_ptr<MaterialManager> m_materialManager;
};
} // namespace FIRE

#endif // !FIRE_GLDrawAgent_h
