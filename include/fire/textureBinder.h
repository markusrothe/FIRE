#ifndef fire_texturebinder_h
#define fire_texturebinder_h

#include "binder.h"

namespace Fire
{
class Renderable;

class TextureBinder : public Binder
{
public:
    ~TextureBinder() = default;
    void Bind(Renderable* renderable) const override;
    void Unbind(Renderable* renderable) const override;
};

} // namespace Fire

#endif // fire_texturebinder_h
