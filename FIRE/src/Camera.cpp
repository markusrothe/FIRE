#include <FIRE/Camera.h>

#include "glm_wrapper.h"

namespace FIRE
{
Camera::Camera(
    std::string name,
    Vector3 pos /* = Vertex(0.0f, 0.0f, 0.0f) */,
    Vector3 lookAt /*= Vertex(0.0f, 0.0f, 0.0f) */)
    : m_name(std::move(name))
    , m_pos(std::move(pos))
    , m_lookAt(std::move(lookAt))
{
}

std::string Camera::Name() const
{
    return m_name;
}

void Camera::SetPosition(Vector3 pos)
{
    m_pos = std::move(pos);
}

Vector3 Camera::Position() const
{
    return m_pos;
}

void Camera::SetOrientation(Vector3 lookAt)
{
    m_lookAt = std::move(lookAt);
}

Vector3 Camera::Orientation() const
{
    return m_lookAt;
}

Matrix4x4 Camera::ViewMatrix() const
{
    return CreateViewMatrix(m_pos, m_lookAt, Vector3(0.0f, 1.0f, 0.0f));
}

} // namespace FIRE