#include <FIRE/Camera.h>

#include "glm_wrapper.h"

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
    return CreateViewMatrix(m_pos, m_lookAt, Vertex(0.0f, 1.0f, 0.0f));
}

} // namespace FIRE