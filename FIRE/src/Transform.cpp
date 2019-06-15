#include "glm_wrapper.h"
#include <FIRE/Transform.h>
#include <iostream>
namespace FIRE
{
namespace
{
glm::vec3 ToGlmVec3(Vector3 const& v)
{
    return glm::vec3(v.x, v.y, v.z);
}

Vector3 FromGlmVec3(glm::vec3 const& v)
{
    return Vector3(v.x, v.y, v.z);
}

} // namespace

class Transform::Impl
{
public:
    Impl(Vector3 const& pos, Vector3 const& lookAt)
        : m_pos(ToGlmVec3(pos))
        , m_lookAt(ToGlmVec3(lookAt))
        , m_rotation(1.0, 0.0, 0.0, 0.0)
    {
    }

    Vector3 Position() const
    {
        return FromGlmVec3(m_pos);
    }

    Vector3 LookAt() const
    {
        return FromGlmVec3(m_lookAt);
    }

    Vector3 Right() const
    {
        auto const forward = glm::normalize(m_lookAt - m_pos);
        auto const up{ToGlmVec3(Up())};
        return FromGlmVec3(glm::normalize(glm::cross(forward, up)));
    }

    Vector3 Up() const
    {
        return Vector3(0.0f, 1.0f, 0.0f);
    }

    void SetLookAt(Vector3 const& lookAt)
    {
        m_lookAt = ToGlmVec3(lookAt);
    }

    void Translate(float x, float y, float z)
    {
        m_pos += glm::vec3(x, y, z);
        m_lookAt += glm::vec3(x, y, z);
    }

    void Rotate(Vector3 const& axis, float angle)
    {
        auto quat = glm::angleAxis(glm::radians(angle), glm::normalize(ToGlmVec3(axis)));
        m_rotation = glm::normalize(quat * m_rotation);
        m_lookAt = m_pos + glm::rotate(glm::normalize(m_lookAt - m_pos), glm::radians(angle), glm::normalize(ToGlmVec3(axis)));
    }

    Matrix4x4 ModelMatrix() const
    {
        glm::mat4 mat(1.0f);
        mat = glm::translate(mat, m_pos);
        mat *= glm::toMat4(m_rotation);
        return Matrix4x4(glm_helper::matToArray(mat));
    }

private:
    glm::vec3 m_pos;
    glm::vec3 m_lookAt;
    glm::quat m_rotation;
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

Vector3 Transform::LookAt() const
{
    return m_impl->LookAt();
}

Vector3 Transform::Right() const
{
    return m_impl->Right();
}

Vector3 Transform::Up() const
{
    return m_impl->Up();
}

void Transform::SetLookAt(Vector3 viewDir)
{
    return m_impl->SetLookAt(std::move(viewDir));
}

void Transform::Translate(float x, float y, float z)
{
    m_impl->Translate(x, y, z);
}

void Transform::Translate(Vector3 const& vec)
{
    m_impl->Translate(vec.x, vec.y, vec.z);
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
