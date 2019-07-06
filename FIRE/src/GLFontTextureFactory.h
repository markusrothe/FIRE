#ifndef FIRE_GLFontTextureFactory_h
#define FIRE_GLFontTextureFactory_h

#include "FontTextureFactory.h"
#include <FIRE/glmfwd.h>
#include <glad/glad.h>
#include <map>

namespace FIRE
{
class GLFontTextureFactory : public FontTextureFactory
{
public:
    GLFontTextureFactory();
    FontCharacter CreateTexture(char c) override;

private:
    
    std::map<GLchar, FontCharacter> m_characters;
};
} // namespace FIRE

#endif // FIRE_GLFontTextureFactory_h