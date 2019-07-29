#include "GLRenderer.h"
#include "DrawAgent.h"
#include "FontCharacter.h"
#include "GLShaderFactory.h"
#include "TextureFactory.h"
#include "Uploader.h"
#include <FIRE/Renderable.h>
#include <FIRE/Scene.h>
#include <FIRE/TextOverlay.h>
#include <array>
#include <fstream>
#include <glad/glad.h>

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

std::array<GLfloat, 24> GetFontCharQuad(FontCharacter const& ch, float x, float y, float scale)
{
    GLfloat xpos = x + ch.bearing.x * scale;
    GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scale;

    GLfloat w = (GLfloat)ch.size.x * scale;
    GLfloat h = (GLfloat)ch.size.y * scale;
    return {
        xpos, ypos + h, 0.0, 0.0,
        xpos, ypos, 0.0, 1.0,
        xpos + w, ypos, 1.0, 1.0,

        xpos, ypos + h, 0.0, 0.0,
        xpos + w, ypos, 1.0, 1.0,
        xpos + w, ypos + h, 1.0, 0.0};
}
} // namespace
GLRenderer::GLRenderer(
    std::unique_ptr<Uploader> uploader,
    std::unique_ptr<DrawAgent> drawAgent,
    std::unique_ptr<TextureFactory> texFactory)
    : m_uploader(std::move(uploader))
    , m_drawAgent(std::move(drawAgent))
    , m_texFactory(std::move(texFactory))
{
    GLShaderFactory factory;
    FIRE::Shaders const shaders = {
        {FIRE::ShaderType::VERTEX_SHADER, GetFileContent("textVS.glsl")},
        {FIRE::ShaderType::FRAGMENT_SHADER, GetFileContent("textFS.glsl")}};
    m_texShader = factory.Create(shaders);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glGenVertexArrays(1, &texVAO);
    glGenBuffers(1, &texVBO);
    glBindVertexArray(texVAO);
    glBindBuffer(GL_ARRAY_BUFFER, texVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

GLRenderer::~GLRenderer() = default;

void GLRenderer::Submit(Renderable const& renderable)
{
    m_renderables[renderable.name] = renderable;
}

void GLRenderer::Submit(TextOverlay overlay)
{
    m_overlays[overlay.id] = overlay;
}

void GLRenderer::Render(float windowWidth, float windowHeight)
{
    m_drawAgent->Clear();

    for(auto const& renderable : m_renderables)
    {
        auto buffers = m_uploader->Upload(renderable.second);
        m_drawAgent->Draw(renderable.second, buffers);
    }

    for(auto const& overlay : m_overlays)
    {
        Render(overlay.second, windowWidth, windowHeight);
    }
}

void GLRenderer::Render(TextOverlay const& overlay, float width, float height)
{
    glm::mat4 projection = glm::ortho(0.0f, width, 0.0f, height);

    glUseProgram(m_texShader);
    glUniform3f(glGetUniformLocation(m_texShader, "textColor"), 1.0f, 0.0f, 0.0f);

    glUniformMatrix4fv(glGetUniformLocation(m_texShader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(texVAO);

    float x = overlay.x * width;
    float y = overlay.y * height;

    for(auto const& c : overlay.text)
    {
        FontCharacter* ch = m_texFactory->CreateFontCharTexture(c);

        auto vertices = GetFontCharQuad(*ch, x, y, overlay.scale);

        ch->texture.Bind();

        glBindBuffer(GL_ARRAY_BUFFER, texVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices.data());
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch->advance >> 6) * overlay.scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GLRenderer::ToggleWireframe()
{
    m_drawAgent->ToggleWireframe();
}
} // namespace FIRE
