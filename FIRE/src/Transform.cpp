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
} // namespace

class Transform::Impl
{
public:
    Impl(Vector3 const& pos, Vector3 const& viewDir)
        : m_modelMatrix(glm::translate(ToGlmVec3(pos)))
    {
        SetOrientation(viewDir);
    }

    Vector3 Position() const
    {
        glm::vec3 scale, translation, skew;
        glm::vec4 perspective;
        glm::quat orientation;
        glm::decompose(m_modelMatrix, scale, orientation, translation, skew, perspective);

        return Vector3(translation.x, translation.y, translation.z);
    }

    Vector3 Orientation() const
    {
        glm::vec3 scale, translation, skew;
        glm::vec4 perspective;
        glm::quat orientation;
        glm::decompose(m_modelMatrix, scale, orientation, translation, skew, perspective);

        glm::vec3 const result = glm::normalize(glm::rotate(orientation, ToGlmVec3(m_viewDir)));
        return Vector3(result.x, result.y, result.z);
    }

    Vector3 Right() const
    {
        glm::vec3 const forward{ToGlmVec3(Orientation())};
        glm::vec3 const up{ToGlmVec3(Up())};
        auto right = glm::normalize(glm::cross(glm::normalize(forward), glm::normalize(up)));
        return Vector3(right.x, right.y, right.z);
    }

    Vector3 Up() const
    {
        return Vector3(0.0f, 1.0f, 0.0f);
    }

    void SetOrientation(Vector3 dir)
    {
        m_viewDir = std::move(dir);
    }

    void Translate(float x, float y, float z)
    {
        m_modelMatrix = glm::translate(m_modelMatrix, glm::vec3(x, y, z));
    }

    void Rotate(Vector3 const& axis, float angle)
    {
        m_modelMatrix = glm::rotate(
            m_modelMatrix, glm::radians(angle), ToGlmVec3(axis));
    }

    Matrix4x4 ModelMatrix() const
    {
        return Matrix4x4(glm_helper::matToArray(m_modelMatrix));
    }

private:
    glm::mat4 m_modelMatrix;
    Vector3 m_viewDir;
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

Vector3 Transform::Right() const
{
    return m_impl->Right();
}

Vector3 Transform::Up() const
{
    return m_impl->Up();
}

void Transform::SetOrientation(Vector3 viewDir)
{
    return m_impl->SetOrientation(std::move(viewDir));
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
