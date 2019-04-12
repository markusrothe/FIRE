#pragma warning( push )
#pragma warning( disable : 4201)
#pragma warning( disable : 4127)
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/type_ptr.hpp"
#pragma warning( pop ) 
#include <FIRE/Camera.h>

namespace FIRE
{
Camera::Camera(
    std::string name, 
    Vertex pos /* = Vertex(0.0f, 0.0f, 0.0f) */,
    Vertex lookAt /*= Vertex(0.0f, 0.0f, 0.0f) */)
    : m_name(std::move(name))
    , m_pos(std::move(pos))
    , m_lookAt(std::move(lookAt))
{
}

std::string Camera::Name() const
{
    return m_name;
}

void Camera::SetPosition(Vertex pos)
{
    m_pos = std::move(pos);
}

Vertex Camera::Position() const
{
    return m_pos;
}

void Camera::SetOrientation(Vertex lookAt)
{
    m_lookAt = std::move(lookAt);
}

Vertex Camera::Orientation() const
{
    return m_lookAt;
}

Matrix4x4 Camera::ViewMatrix() const
{
    glm::vec3 const pos(m_pos.x, m_pos.y, m_pos.z);
    glm::vec3 const lookAt(m_lookAt.x, m_lookAt.y, m_lookAt.z);
    glm::vec3 const up(0.0f, 1.0f, 0.0f);
    glm::mat4 const view = glm::lookAt(pos, lookAt, up);
    return Matrix4x4({
            view[0][0],
            view[0][1],
            view[0][2],
            view[0][3],
            view[1][0],
            view[1][1],
            view[1][2],
            view[1][3],
            view[2][0],
            view[2][1],
            view[2][2],
            view[2][3],
            view[3][0],
            view[3][1],
            view[3][2],
            view[3][3]
        });
}

Matrix4x4 Camera::PerspectiveMatrix() const
{
    glm::mat4 const perspective = glm::perspective(20.0f, 800.0f / 600.0f, 0.01f, 10.0f);

    return Matrix4x4({
            perspective[0][0],
            perspective[0][1],
            perspective[0][2],
            perspective[0][3],
            perspective[1][0],
            perspective[1][1],
            perspective[1][2],
            perspective[1][3],
            perspective[2][0],
            perspective[2][1],
            perspective[2][2],
            perspective[2][3],
            perspective[3][0],
            perspective[3][1],
            perspective[3][2],
            perspective[3][3]
        });
}

} // namespace FIRE