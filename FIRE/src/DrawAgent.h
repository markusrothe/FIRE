#ifndef FIRE_DrawAgent_h
#define FIRE_DrawAgent_h
#include "GLBuffer.h"
#include <tuple>

namespace FIRE
{
class Renderable;
class DrawAgent
{
public:
    virtual ~DrawAgent() = default;

    virtual void Draw(Renderable const&, GLVertexArrayObject buffers) = 0;

    virtual void Clear() = 0;
};

} // namespace FIRE

#endif // !FIRE_DrawAgent_h
