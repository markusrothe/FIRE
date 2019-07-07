#ifndef FIRE_Camera_H
#define FIRE_Camera_H

#include <FIRE/Transform.h>
#include <FIRE/glmfwd.h>
#include <string>

namespace FIRE
{
class Camera
{
public:
    explicit Camera(
        std::string name,
        glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 viewDir = glm::vec3(0.0f, 0.0f, -1.0f));

    std::string Name() const;

    Transform& GetTransform();

    glm::mat4x4 ViewMatrix() const;

private:
    std::string const m_name;
    Transform m_transform;
};

bool operator==(Camera const& lhs, Camera const& rhs);
bool operator!=(Camera const& lhs, Camera const& rhs);

} // namespace FIRE

#endif // !FIRE_Camera_H
