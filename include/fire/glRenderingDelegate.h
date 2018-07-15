#ifndef fire_glrenderingdelegate_h
#define fire_glrenderingdelegate_h

#include "renderingDelegate.h"
#include <GL/glew.h>
#include <tuple>
#include <unordered_map>

namespace Fire
{
class Renderable;

class GLRenderingDelegate : public RenderingDelegate
{
public:
    void Bind(Renderable* renderable) override;
    void Render(Renderable* renderable) override;
    void Unbind(Renderable* renderable) override;

private:
    void UploadRenderable(Renderable* renderable);

    typedef std::tuple<GLuint, GLuint, GLuint> BufferObjects;
    std::unordered_map<Renderable*, BufferObjects> m_uploadedRenderables;
};
} // namespace Fire

#endif // fire_glrenderingdelegate_h
