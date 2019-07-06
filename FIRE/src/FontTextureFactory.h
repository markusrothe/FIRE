#ifndef FIRE_FontTextureFactory_h
#define FIRE_FontTextureFactory_h

#include "FontCharacter.h"

namespace FIRE
{
class FontTextureFactory
{
public:
    virtual ~FontTextureFactory() = default;
    virtual FontCharacter CreateTexture(char c) = 0;
};
} // namespace FIRE

#endif // FIRE_FontTextureFactory_h