#include <FIRE/Camera.h>
#include <FIRE/glmfwd.h>

namespace FIRE
{
Camera::Camera(
    std::string name,
    glm::vec3 pos /* = Vertex(0.0f, 0.0f, 0.0f) */,
    glm::vec3 viewDir /*= Vertex(0.0f, 0.0f, -1.0f) */)
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

glm::mat4x4 Camera::ViewMatrix() const
{
    return glm::lookAt(m_transform.Position(), m_transform.LookAt(), m_transform.Up());
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
