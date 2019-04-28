#ifndef FIRE_Transform_h
#define FIRE_Transform_h

#include <FIRE/Matrix.h>
#include <FIRE/Vector.h>

namespace FIRE
{
class Transform
{
public:
    explicit Transform(Vector3 pos = Vector3(0.0f, 0.0f, 0.0f));
    Vector3 Position() const;
    void Translate(float x, float y, float z);
    Matrix4x4 ModelMatrix() const;

private:
    Vector3 m_position;
};
} // namespace FIRE

#endif // FIRE_Transform_h
