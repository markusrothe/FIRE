#ifndef blocks_fontManager_h
#define blocks_fontManager_h

#include "texture.h"
#include <unordered_map>

namespace blocks
{
    class FontManager
    {
    public:
        FontManager();

        CharTexture const* GetCharTexture(char c) const;

    private:

        std::unordered_map<char, CharTexture> m_charTextures;
    };
}

#endif // blocks_fontManager_h
