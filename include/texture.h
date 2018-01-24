#ifndef blocks_texture_h
#define blocks_texture_h

#include <string>
#include <GL/glew.h>

namespace blocks
{
    class Texture
    {
    public:
        Texture();
        Texture(std::string const imageFilePath, bool cubemap);

        void Bind();
        void Unbind();

        GLuint GetBindingID() const;
        
    private:
        GLuint m_textureBinding;
        unsigned int m_texOffset;
        bool m_cubemap;
    };
}

#endif // blocks_texture_h
