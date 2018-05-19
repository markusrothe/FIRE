#ifndef fire_texture_h
#define fire_texture_h

namespace Fire
{
    class Texture
    {
    public:
        virtual ~Texture() = default;
        
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual bool Bound() const = 0;
    };
} // namespace Fire

#endif //fire_texture_h
