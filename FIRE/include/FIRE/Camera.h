#ifndef FIRE_Camera_H
#define FIRE_Camera_H

#include <FIRE/Vertex.h>
#include <FIRE/Matrix.h>
#include <string>


namespace FIRE
{
class Camera
{
public:
    explicit Camera(
        std::string name, 
        Vertex pos = Vertex(0.0f, 0.0f, 0.0f), 
        Vertex lookAt = Vertex(0.0f, 0.0f, 0.0f));

    std::string Name() const;

    void SetPosition(Vertex pos);
    Vertex Position() const;

    void SetOrientation(Vertex lookAt);
    Vertex Orientation() const;

    Matrix4x4 ViewMatrix() const;

private:
    std::string const m_name;
    Vertex m_pos;
    Vertex m_lookAt;
};
} // namespace FIRE

#endif // !FIRE_Camera_H
