#include "texture.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace blocks
{
    unsigned int texOffset = 0;

    Texture::Texture()
        : m_textureBinding(0)
    {

    }

    Texture::Texture(std::string const imageFilePath, bool cubemap)
        : m_textureBinding(0)
        , m_texOffset(texOffset++)
        , m_cubemap(cubemap)
    {
        int x, y, n;
        unsigned char* data = stbi_load(imageFilePath.c_str(), &x, &y, &n, 3);

        glActiveTexture(GL_TEXTURE0);

        if (m_cubemap)
        {
            glEnable(GL_TEXTURE_CUBE_MAP);
            glGenTextures(1, &m_textureBinding);
            glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureBinding);
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

        }
        else
        {
            glEnable(GL_TEXTURE_2D);
            glGenTextures(1, &m_textureBinding);
            glBindTexture(GL_TEXTURE_2D, m_textureBinding);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, 16);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        stbi_image_free(data);

        std::cout << "Loading texture from file " << imageFilePath << " done" << std::endl;
    }

    void Texture::Bind()
    {
        glActiveTexture(GL_TEXTURE0);
        if (m_cubemap)
        {
            glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureBinding);
        }
        else
        {
            glBindTexture(GL_TEXTURE_2D, m_textureBinding);
        }
    }

    void Texture::Unbind()
    {
        if (m_cubemap)
        {
            glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
        }
        else
        {
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }

    GLuint Texture::GetBindingID() const
    {
        return m_textureBinding;
    }
}
