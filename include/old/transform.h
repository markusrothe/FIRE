#ifndef blocks_transform_h
#define blocks_transform_h

#include "glmForward.h"

namespace blocks
{
    class Transform
    {
    public:

        Transform();

        glm::mat4x4 GetModelMatrix() const;

        glm::vec3 GetPosition() const;
        glm::vec3 GetRightVector() const;
        glm::vec3 GetForwardVector() const;
        glm::vec3 GetUpVector() const;

        void Translate(float x, float y, float z);
        void Translate(glm::vec3 const& translation);
        void Scale(float scaleFactor);

        void Pitch(float angle);
        void Yaw(float angle);

    private:
        glm::vec3 m_position;
        glm::vec3 m_scale;
        glm::quat m_orientation;
    };
}

#endif // blocks_transform_h
