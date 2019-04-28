#include <FIRE/Transform.h>

namespace FIRE
{
Transform::Transform(Vector3 pos /* = Vector3(0.0f, 0.0f, 0.0f) */)
    : m_position(std::move(pos))
{
}

Vector3 Transform::Position() const
{
    return m_position;
}

void Transform::Translate(float x, float y, float z)
{
    m_position += Vector3(x, y, z);
}

Matrix4x4 Transform::ModelMatrix() const
{
    Matrix4x4 mat;
    mat.At(3, 0) = m_position.x;
    mat.At(3, 1) = m_position.y;
    mat.At(3, 2) = m_position.z;
    return mat;
}
} // namespace FIRE
