#ifndef FIRE_FontLoader_h
#define FIRE_FontLoader_h

#include "FIRE/FontCharacter.h"

namespace FIRE
{
class FontLoader
{
public:
    virtual ~FontLoader() = default;
    virtual FontCharacter LoadChar(char c) = 0;
};
} // namespace FIRE

#endif // FIRE_FontLoader_h
