#ifndef FIRE_VAO_h
#define FIRE_VAO_h

namespace FIRE
{
using VAO = unsigned int;
using VBO = unsigned int;
using IBO = unsigned int;

struct GLVertexArrayObject
{
    GLVertexArrayObject(VAO vao, VBO vbo, IBO ibo)
        : m_vao(vao)
        , m_vbo(vbo)
        , m_ibo(ibo)
    {
    }

    VAO m_vao;
    VBO m_vbo;
    IBO m_ibo;
};

} // namespace FIRE

#endif // FIRE_VAO_h
