#include "GLDrawAgent.h"
#include "MaterialManager.h"
#include <FIRE/Renderable.h>

namespace FIRE
{
GLDrawAgent::GLDrawAgent(std::shared_ptr<MaterialManager> materialManager)
    : m_materialManager(std::move(materialManager))
{
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void GLDrawAgent::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLDrawAgent::Draw(
    Renderable const& renderable, std::tuple<GLuint, GLuint, GLuint> buffers)
{
    glBindVertexArray(std::get<0>(buffers));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, std::get<2>(buffers));
    auto const shader = m_materialManager->GetShader(renderable.GetMaterial());
    glUseProgram(shader);
    auto const uniformVal = renderable.GetShaderUniformMat4x4();
    auto const uniformLocation = glGetUniformLocation(shader, uniformVal.first.c_str());
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, uniformVal.second.Raw().data());

    glDrawElements(
        GL_TRIANGLES, static_cast<GLsizei>(renderable.GetMesh().Indices().size()), GL_UNSIGNED_INT, 0);

    glUseProgram(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

} // namespace FIRE
