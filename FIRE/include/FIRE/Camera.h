#ifndef FIRE_Camera_H
#define FIRE_Camera_H

#include <FIRE/Matrix.h>
#include <FIRE/Transform.h>
#include <FIRE/Vector.h>
#include <string>

namespace FIRE
{
class Camera
{
public:
    explicit Camera(
        std::string name,
        Vector3 pos = Vector3(0.0f, 0.0f, 0.0f),
        Vector3 viewDir = Vector3(0.0f, 0.0f, -1.0f));

    std::string Name() const;

    Transform& GetTransform();

    Matrix4x4 ViewMatrix() const;

private:
    std::string const m_name;
    Transform m_transform;
};
} // namespace FIRE

#endif // !FIRE_Camera_H
