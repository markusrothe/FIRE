#ifndef FIRE_Transform_h
#define FIRE_Transform_h

#include <FIRE/glmfwd.h>
#include <memory>

namespace FIRE
{

class Transform
{
public:
    explicit Transform(
        glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 lookAt = glm::vec3(0.0f, 0.0f, -1.0f));

    glm::vec3 Position() const;
    glm::vec3 LookAt() const;
    glm::vec3 GetScaling() const;
    glm::vec3 Right() const;
    glm::vec3 Up() const;
    void SetPosition(glm::vec3 pos);
    void SetLookAt(glm::vec3 dir);
    void Translate(float x, float y, float z);
    void Translate(glm::vec3 const& vec);
    void Rotate(glm::vec3 const& axis, float angle);
    void Scale(glm::vec3 const& scale);

    glm::mat4x4 ModelMatrix() const;

private:
    glm::vec3 m_pos;
    glm::vec3 m_scale;
    glm::vec3 m_lookAt;
    glm::quat m_rotation;
};
} // namespace FIRE

#endif // FIRE_Transform_h
