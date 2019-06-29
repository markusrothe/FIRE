#include <FIRE/Camera.h>

#include "glm_wrapper.h"

namespace FIRE
{
Camera::Camera(
    std::string name,
    Vector3 pos /* = Vertex(0.0f, 0.0f, 0.0f) */,
    Vector3 viewDir /*= Vertex(0.0f, 0.0f, -1.0f) */)
    : m_name(std::move(name))
    , m_transform(pos, viewDir)
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

Matrix4x4 Camera::ViewMatrix() const
{
    return CreateViewMatrix(m_transform.Position(), m_transform.LookAt(), m_transform.Up());
}

bool operator==(FIRE::Camera const& lhs, FIRE::Camera const& rhs)
{
    return lhs.Name() == rhs.Name();
}

bool operator!=(FIRE::Camera const& lhs, FIRE::Camera const& rhs)
{
    return !(lhs == rhs);
}
} // namespace FIRE
