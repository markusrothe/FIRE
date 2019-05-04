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
    Vector3 Orientation() const;
    void SetOrientation(Vector3 lookAt);

    void Translate(float x, float y, float z);
    void Rotate(Vector3 const& axis, float angle);

    Matrix4x4 ModelMatrix() const;

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};
} // namespace FIRE

#endif // FIRE_Transform_h
