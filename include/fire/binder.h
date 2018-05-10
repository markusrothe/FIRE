#ifndef fire_binder_h
#define fire_binder_h

namespace Fire
{
    class Renderable;
    class Binder
    {
    public:

        virtual ~Binder() = default;

        Binder(Binder const&) = delete;
        Binder& operator=(Binder const&) = delete;
        Binder(Binder&&) = delete;
        Binder& operator=(Binder&&) = delete;

        virtual void Bind(Renderable* renderable) const = 0;
        virtual void Unbind(Renderable* renderable) const = 0;

    protected:

        Binder() = default;

    };

} // namespace Fire

#endif // fire_binder_h
