#include "GLTextRenderer.h"
#include "FontCharacter.h"
#include "GLShaderFactory.h"
#include "TextureFactory.h"
#include <FIRE/TextOverlay.h>
#include <FIRE/glmfwd.h>

#include <glad/glad.h>

#include <fstream>
#include <iostream>
#include <iterator>

namespace FIRE
{
namespace
{
std::string GetFileContent(std::string const& filePath)
{
    std::ifstream file(filePath);
    std::string const content{(std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()};
    return content;
}
} // namespace

GLTextRenderer::GLTextRenderer(std::unique_ptr<TextureFactory> texFactory)
    : m_texFactory(std::move(texFactory))
{
    GLShaderFactory factory;
    FIRE::Shaders const shaders = {
        {FIRE::ShaderType::VERTEX_SHADER, GetFileContent("textVS.glsl")},
        {FIRE::ShaderType::FRAGMENT_SHADER, GetFileContent("textFS.glsl")}};
    m_texShader = factory.Create(shaders);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

GLTextRenderer::~GLTextRenderer() = default;

void GLTextRenderer::Render(TextOverlay overlay)
{
    GLuint texVAO, texVBO;

    glGenVertexArrays(1, &texVAO);
    glGenBuffers(1, &texVBO);
    glBindVertexArray(texVAO);
    glBindBuffer(GL_ARRAY_BUFFER, texVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Activate corresponding render state
    glUseProgram(m_texShader);
    glUniform3f(glGetUniformLocation(m_texShader, "textColor"), 1.0f, 1.0f, 1.0f);

    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
    glUniformMatrix4fv(glGetUniformLocation(m_texShader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(texVAO);
    float x = 030.0f;
    float y = 500.0f;
    float scale = 0.5f;
    // Iterate through all characters
    std::string::const_iterator c;
    auto text = overlay.GetText();
    for(c = text.begin(); c != text.end(); c++)
    {
        FontCharacter ch = m_texFactory->CreateFontCharTexture(*c);

        GLfloat xpos = x + ch.bearing.x * scale;
        GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scale;

        GLfloat w = (GLfloat)ch.size.x * scale;
        GLfloat h = (GLfloat)ch.size.y * scale;
        // Update VBO for each character
        GLfloat vertices[6][4] = {
            {xpos, ypos + h, 0.0, 0.0},
            {xpos, ypos, 0.0, 1.0},
            {xpos + w, ypos, 1.0, 1.0},

            {xpos, ypos + h, 0.0, 0.0},
            {xpos + w, ypos, 1.0, 1.0},
            {xpos + w, ypos + h, 1.0, 0.0}};
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.textureID);
        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, texVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

} // namespace FIRE
