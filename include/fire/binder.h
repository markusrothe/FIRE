#ifndef fire_binder_h
#define fire_binder_h

namespace Fire
{
class Renderable;
class Binder
{
public:
    virtual ~Binder() = default;

    virtual void Bind(Renderable* renderable) const = 0;
    virtual void Unbind(Renderable* renderable) const = 0;
};

} // namespace Fire

#endif // fire_binder_h
