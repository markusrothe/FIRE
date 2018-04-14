#ifndef blocks_texture_h
#define blocks_texture_h

#include <string>
#include <GL/glew.h>
#include "glmForward.h"

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
        CharTexture(int bitmapWidth, int bitmapRows, int bitmapLeft, int bitmapTop, int offsetToNextGlyph, void* pixels);

        glm::ivec2 const& GetSize() const;
        glm::ivec2 const& GetBearing() const;
        unsigned int GetOffsetToNextGlyph() const;

        virtual void Bind() override;
        virtual void Unbind() override;

    private:
        glm::ivec2 m_size;
        glm::ivec2 m_bearing;
        unsigned int m_offsetToNextGlyph;
    };
}

#endif // blocks_texture_h
