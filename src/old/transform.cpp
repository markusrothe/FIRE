#include "transform.h"

namespace blocks
{
    namespace
    {
        glm::vec3 const rightVector(1.0f, 0.0f, 0.0f);
        glm::vec3 const upVector(0.0f, 1.0f, 0.0f);
        glm::vec3 const forwardVector(0.0f, 0.0f, 1.0f);
    }

    Transform::Transform()
        : m_position(0.0f, 0.0f, 0.0f)
        , m_scale(1.0f, 1.0f, 1.0f)
        , m_orientation()
    {

    }

    glm::mat4x4 Transform::GetModelMatrix() const
    {
        auto rotation = glm::mat4_cast(m_orientation);
        auto translation = glm::translate(glm::mat4x4(1.0f), m_position);
        auto scale = glm::scale(glm::mat4x4(1.0f), m_scale);
        return scale * rotation * translation;
    }

    glm::vec3 Transform::GetPosition() const
    {
        return m_position;
    }

    glm::vec3 Transform::GetRightVector() const
    {
        return glm::conjugate(m_orientation) * rightVector;
    }

    glm::vec3 Transform::GetForwardVector() const
    {
        return glm::conjugate(m_orientation) * forwardVector;
    }

    glm::vec3 Transform::GetUpVector() const
    {
        return glm::conjugate(m_orientation) * upVector;
    }

    void Transform::Translate(float x, float y, float z)
    {
        Translate(glm::vec3(x, y, z));
    }

    void Transform::Translate(glm::vec3 const& translation)
    {
        m_position += translation;
    }

    void Transform::Scale(float scaleFactor)
    {
        m_scale *= scaleFactor;
    }

    void Transform::Pitch(float angle)
    {
        auto const rotation = glm::angleAxis(glm::pi<float>() / 180.0f * angle, rightVector);
        m_orientation = rotation * m_orientation;
        m_orientation = glm::normalize(m_orientation);
    }

    void Transform::Yaw(float angle)
    {
        auto const rotation = glm::angleAxis(glm::pi<float>() / 180.0f * angle, upVector);
        m_orientation = rotation * m_orientation;
        m_orientation = glm::normalize(m_orientation);
    }
} // namespace blocks
