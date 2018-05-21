#include "texture.h"

namespace Fire
{
    namespace
    {
        GLenum MapTextureTarget(Texture::TextureType target)
        {
            switch(target)
            {
            case Texture::TextureType::Image2D:
                return GL_TEXTURE_2D;
            case Texture::TextureType::Image3D:
                return GL_TEXTURE_3D;
            default:
                return GL_NONE;
            };
        }
    } // namespace
    
    GLTexture(unsigned int slot, TextureType target)
        : m_slot(slot)
        , m_target(MapTextureTarget(target))
        , m_id(0)
        , m_bound(false)
    {
        if (m_target != GL_NONE)
        {
            glActiveTexture(GL_TEXTURE0 + m_slot);
            glEnable(m_target);
            glGenTextures(1, &m_id);
            /* TODO: 
               glBindTexture(GL_TEXTURE_2D, m_binding);
               
               glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
               glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
               glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
               glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
               glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, 16);
               glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
               
               glGenerateMipmap(GL_TEXTURE_2D);
             */
            
        }
    }
        
    void Bind() override
    {
        if (m_target != GL_NONE)
        {
            glActiveTexture(GL_TEXTURE0 + m_slot);
            glBindTexture(m_target, m_id);
            m_bound = true;
        }       
    }
    
    void Unbind() override
    {
        if (m_target != GL_NONE)
        {
            glActiveTexture(GL_TEXTURE0 + m_slot);
            glBindTexture(m_target, 0);
            m_bound = false;
        }
    }
    
    bool Bound() const override
    {
        return m_bound;
    }
}
