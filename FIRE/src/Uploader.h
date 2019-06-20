#ifndef FIRE_Uploader_h
#define FIRE_Uploader_h

#include "GLBuffer.h"
#include <tuple>

namespace FIRE
{
class Renderable;
class Uploader
{
public:
    virtual ~Uploader() = default;

    virtual GLVertexArrayObject Upload(Renderable const& renderable) = 0;
};
} // namespace FIRE

#endif
