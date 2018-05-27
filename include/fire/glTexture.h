#ifndef fire_gltexture_h
#define fire_gltexture_h

#include "texture.h"
#include <GL/glew.h>

namespace Fire
{
    class GLTexture : public Texture
    {
    public:
        GLTexture(unsigned int slot, TextureType target);
        
        void Bind() override;
        void Unbind() override;
        bool Bound() const override;
        
    private:
        unsigned int const m_slot;
        GLenum const m_textureTarget;
        GLuint m_id;
        bool m_bound;
    };
} // namespace Fire

#endif // fire_gltexture_h
