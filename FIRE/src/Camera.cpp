#include <FIRE/Camera.h>

#include "glm_wrapper.h"

namespace FIRE
{
Camera::Camera(
    std::string name,
    Vector3 pos /* = Vertex(0.0f, 0.0f, 0.0f) */,
    Vector3 lookAt /*= Vertex(0.0f, 0.0f, 0.0f) */)
    : m_name(std::move(name))
    , m_transform(pos)
    , m_lookAt(std::move(lookAt))
{
}

std::string Camera::Name() const
{
    return m_name;
}

Transform& Camera::GetTransform()
{
    return m_transform;
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
    return CreateViewMatrix(m_transform.Position(), m_lookAt, Vector3(0.0f, 1.0f, 0.0f));
}

} // namespace FIRE
