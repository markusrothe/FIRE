#ifndef blocks_texture_h
#define blocks_texture_h

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace blocks
{
    class Texture
    {
    public:        
        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        GLuint GetBinding() const { return m_binding; }
        
    protected:
        explicit Texture(GLuint binding);
        
        GLuint m_binding;
    };

    class ImageTexture : public Texture
    {
    public:
        explicit ImageTexture(std::string const& imageFilePath);
        
        virtual void Bind() override;
        virtual void Unbind() override;
    };

    class CubemapTexture : public Texture
    {
    public:
        explicit CubemapTexture(std::string const& imageFilePath);
        
        virtual void Bind() override;
        virtual void Unbind() override;
    };

    class CharTexture : public Texture
    {
    public:
        explicit CharTexture(char const c);
        
        virtual void Bind() override;
        virtual void Unbind() override;

    private:
        char m_char;
        glm::ivec2 m_size;
        glm::ivec2 m_bearing;
        unsigned int m_offsetToNextGlyph;
    };
}

#endif // blocks_texture_h
