#ifndef FIRE_FTFontLoader_h
#define FIRE_FTFontLoader_h

#include "FIRE/FontCharacter.h"
#include "FontLoader.h"

namespace FIRE
{
class FTFontLoader : public FontLoader
{
public:
    FontCharacter LoadChar(char c) override;
};
} // namespace FIRE

#endif // FIRE_FTFontLoader_h
