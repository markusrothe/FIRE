#ifndef FIRE_Camera_H
#define FIRE_Camera_H

#include <FIRE/Vector.h>
#include <FIRE/Matrix.h>
#include <string>


namespace FIRE
{
class Camera
{
public:
    explicit Camera(
        std::string name, 
        Vector3 pos = Vector3(0.0f, 0.0f, 0.0f),
        Vector3 lookAt = Vector3(0.0f, 0.0f, 0.0f));

    std::string Name() const;

    void SetPosition(Vector3 pos);
    Vector3 Position() const;

    void SetOrientation(Vector3 lookAt);
    Vector3 Orientation() const;

    Matrix4x4 ViewMatrix() const;

private:
    std::string const m_name;
    Vector3 m_pos;
    Vector3 m_lookAt;
};
} // namespace FIRE

#endif // !FIRE_Camera_H
