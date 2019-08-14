#ifndef FIRE_RENDERABLESUBMITTER_H
#define FIRE_RENDERABLESUBMITTER_H

namespace FIRE
{
struct Renderable;
class RenderableSubmitter
{
public:
    virtual ~RenderableSubmitter() = default;
    virtual void Submit(Renderable const& renderable) = 0;
};
} // namespace FIRE

#endif //FIRE_RENDERABLESUBMITTER_H
