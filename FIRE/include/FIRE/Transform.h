#ifndef FIRE_Transform_h
#define FIRE_Transform_h

#include <FIRE/Matrix.h>
#include <FIRE/Vector.h>
#include <memory>

namespace FIRE
{

class Transform
{
public:
    explicit Transform(
        Vector3 pos = Vector3(0.0f, 0.0f, 0.0f),
        Vector3 lookAt = Vector3(0.0f, 0.0f, -1.0f));

    ~Transform();

    Vector3 Position() const;
    Vector3 LookAt() const;
    Vector3 GetScaling() const;
    Vector3 Right() const;
    Vector3 Up() const;
    void SetLookAt(Vector3 dir);

    void Translate(float x, float y, float z);
    void Translate(Vector3 const& vec);
    void Rotate(Vector3 const& axis, float angle);
    void Scale(Vector3 const& scale);

    Matrix4x4 ModelMatrix() const;

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};
} // namespace FIRE

#endif // FIRE_Transform_h
