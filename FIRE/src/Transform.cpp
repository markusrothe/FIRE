#include "glm_wrapper.h"
#include <FIRE/Transform.h>
#include <iostream>
namespace FIRE
{
namespace
{
glm::vec3 constexpr up{0.0f, 1.0f, 0.0f};
}

class Transform::Impl
{
public:
    Impl(Vector3 const& pos, Vector3 const& lookAt)
        : m_position(pos.x, pos.y, pos.z)
        , m_lookAt(lookAt.x, lookAt.y, lookAt.z)
    {
    }

    Vector3 Position() const
    {
        return Vector3(m_position.x, m_position.y, m_position.z);
    }

    Vector3 Orientation() const
    {
        return Vector3(m_lookAt.x, m_lookAt.y, m_lookAt.z);
    }

    void SetOrientation(Vector3 const& lookAt)
    {
        m_lookAt.x = lookAt.x;
        m_lookAt.y = lookAt.y;
        m_lookAt.z = lookAt.z;
    }

    void Translate(float x, float y, float z)
    {
        m_position += glm::vec3(x, y, z);
    }

    void Rotate(Vector3 const& axis, float angle)
    {
        m_lookAt = glm::rotate(
            m_lookAt,
            glm::radians(angle),
            glm::vec3(axis.x, axis.y, axis.z));
    }

    Matrix4x4 ModelMatrix() const
    {
        auto modelMatrix = glm::translate(m_position);
        auto const lookAtMat = glm::lookAt(m_position, m_lookAt, up);
        modelMatrix *= glm::mat4_cast(glm::conjugate(glm::toQuat(lookAtMat)));

        return Matrix4x4(glm_helper::matToArray(modelMatrix));
    }

private:
    glm::vec3 m_position;
    glm::vec3 m_lookAt;
};

Transform::Transform(
    Vector3 pos /* = Vector3(0.0f, 0.0f, 0.0f) */,
    Vector3 lookAt /* = Vector3(0.0f, 0.0f, -1.0f) */)
    : m_impl(std::make_unique<Transform::Impl>(pos, lookAt))
{
}

Transform::~Transform() = default;

Vector3 Transform::Position() const
{
    return m_impl->Position();
}

Vector3 Transform::Orientation() const
{
    return m_impl->Orientation();
}

void Transform::SetOrientation(Vector3 lookAt)
{
    return m_impl->SetOrientation(std::move(lookAt));
}

void Transform::Translate(float x, float y, float z)
{
    m_impl->Translate(x, y, z);
}

void Transform::Rotate(Vector3 const& axis, float angle)
{
    m_impl->Rotate(axis, angle);
}

Matrix4x4 Transform::ModelMatrix() const
{
    return m_impl->ModelMatrix();
}
} // namespace FIRE
