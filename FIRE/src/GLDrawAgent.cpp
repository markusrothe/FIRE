#include "GLDrawAgent.h"
#include <FIRE/Renderable.h>

namespace FIRE
{
void GLDrawAgent::Draw(
    Renderable const& renderable, std::tuple<GLuint, GLuint, GLuint> buffers)
{
    glBindVertexArray(std::get<0>(buffers));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, std::get<2>(buffers));
    glDrawElements(
        GL_TRIANGLES, static_cast<GLsizei>(renderable.GetMesh().Indices().size()), GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}
} // namespace FIRE
