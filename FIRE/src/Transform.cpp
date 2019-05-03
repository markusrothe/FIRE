#include "glm_wrapper.h"
#include <FIRE/Transform.h>
#include <iostream>
namespace FIRE
{

class Transform::Impl
{
public:
    Impl(Vector3 pos)
        : m_position(std::move(pos))
        , m_lookAt(0.0f, 0.0f, -1.0f)
    {
    }

    Vector3 Position() const
    {
        return m_position;
    }

    Vector3 Orientation() const
    {
        return m_lookAt;
    }

    void Translate(float x, float y, float z)
    {
        m_position += Vector3(x, y, z);
    }

    void Rotate(Vector3 const& axis, float angle)
    {
        auto const result = glm::rotate(
            glm::vec3(m_lookAt.x, m_lookAt.y, m_lookAt.z),
            glm::radians(angle),
            glm::vec3(axis.x, axis.y, axis.z));

        m_lookAt = Vector3(result.x, result.y, result.z);
    }

    Matrix4x4 ModelMatrix() const
    {
        auto quat = glm::rotation(
            glm::vec3(0.0f, 0.0f, -1.0f),
            glm::vec3(m_lookAt.x, m_lookAt.y, m_lookAt.z));

        glm::mat4x4 mat(1.0f);
        mat = glm::translate(mat, glm::vec3(m_position.x, m_position.y, m_position.z)) * glm::toMat4(quat);

        return Matrix4x4(glm_helper::matToArray(mat));
    }

private:
    Vector3 m_position;
    Vector3 m_lookAt;
};

Transform::Transform(Vector3 pos /* = Vector3(0.0f, 0.0f, 0.0f) */)
    : m_impl(std::make_unique<Transform::Impl>(std::move(pos)))
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
