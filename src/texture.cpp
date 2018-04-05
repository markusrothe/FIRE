#include "texture.h"
#include <iostream>

#include <ft2build.h>
#include FT_FREETYPE_H

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace blocks
{
    Texture::Texture(GLuint binding)
        : m_binding(binding)
    {

    }
    
    ImageTexture::ImageTexture(std::string const& imageFilePath)
        : Texture(0)
    {
        int x, y, n;
        unsigned char* data = stbi_load(imageFilePath.c_str(), &x, &y, &n, 3);
        
        glActiveTexture(GL_TEXTURE0);
        glEnable(GL_TEXTURE_2D);
        glGenTextures(1, &m_binding);
        glBindTexture(GL_TEXTURE_2D, m_binding);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, 16);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }
    
    void ImageTexture::Bind()
    {
        glBindTexture(GL_TEXTURE_2D, m_binding);
    }

    void ImageTexture::Unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    CubemapTexture::CubemapTexture(std::string const& imageFilePath)
        : Texture(0)
    {
        int x, y, n;
        unsigned char* data = stbi_load(imageFilePath.c_str(), &x, &y, &n, 3);

        glEnable(GL_TEXTURE_CUBE_MAP);
        glGenTextures(1, &m_binding);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_binding);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glDisable(GL_TEXTURE_CUBE_MAP);

        stbi_image_free(data);
    }

    void CubemapTexture::Bind()
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_binding);
    }

    void CubemapTexture::Unbind()
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

    CharTexture::CharTexture(char const c)
        : Texture(0)
    {
        
    }

    void CharTexture::Bind()
    {

    }

    void CharTexture::Unbind()
    {

    }

    
} // namespace blocks
