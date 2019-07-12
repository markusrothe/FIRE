#include <FIRE/Transform.h>
namespace FIRE
{

Transform::Transform(
    glm::vec3 pos /* = glm::vec3(0.0f, 0.0f, 0.0f) */,
    glm::vec3 lookAt /* = glm::vec3(0.0f, 0.0f, -1.0f) */)
    : m_pos(pos)
    , m_scale(1.0f, 1.0f, 1.0f)
    , m_lookAt(lookAt)
    , m_rotation(1.0, 0.0, 0.0, 0.0)
    , m_acceleration(0.0f, 0.0f, 0.0f)
{
}

glm::vec3 Transform::Position() const
{
    return m_pos;
}

glm::vec3 Transform::Acceleration() const
{
    return m_acceleration;
}

glm::vec3 Transform::LookAt() const
{
    return m_lookAt;
}

glm::vec3 Transform::GetScaling() const
{
    return m_scale;
}

glm::vec3 Transform::Right() const
{
    auto const forward = glm::normalize(m_lookAt - m_pos);
    auto const up{Up()};
    return glm::normalize(glm::cross(forward, up));
}

glm::vec3 Transform::Up() const
{
    return glm::vec3(0.0f, 1.0f, 0.0f);
}

void Transform::SetPosition(glm::vec3 pos)
{
    auto const viewDir = m_lookAt - m_pos;
    m_pos = pos;
    m_lookAt = m_pos + viewDir;
}

void Transform::SetAcceleration(glm::vec3 acceleration)
{
    m_acceleration = std::move(acceleration);
}

void Transform::SetLookAt(glm::vec3 lookAt)
{
    m_lookAt = std::move(lookAt);
}

void Transform::Translate(float x, float y, float z)
{
    Translate(glm::vec3(x, y, z));
}

void Transform::Translate(glm::vec3 const& vec)
{
    m_pos += vec;
    m_lookAt += vec;
}

void Transform::Accelerate(glm::vec3 const& vec)
{
    m_acceleration += vec;
}

void Transform::Rotate(glm::vec3 const& axis, float angle)
{
    auto quat = glm::angleAxis(glm::radians(angle), glm::normalize(axis));
    m_rotation = glm::normalize(quat * m_rotation);
    m_lookAt = m_pos + glm::rotate(glm::normalize(m_lookAt - m_pos), glm::radians(angle), glm::normalize(axis));
}

void Transform::Scale(glm::vec3 const& scale)
{
    m_scale *= scale;
}

glm::mat4x4 Transform::ModelMatrix() const
{
    return glm::translate(m_pos) * glm::toMat4(m_rotation) * glm::scale(m_scale);
}
} // namespace FIRE
