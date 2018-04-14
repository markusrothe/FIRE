#ifndef blocks_camera_h
#define blocks_camera_h

#include "keyhandlerListener.h"
#include "transform.h"
#include "glmForward.h"

namespace blocks
{
    class Camera : public KeyHandlerListener
    {
    public:
        Camera(glm::vec3 const& position, float fovy, float near, float far, float viewportWidth, float viewportHeight);

        glm::mat4 GetProjectionMatrix() const;
        glm::mat4 GetViewMatrix() const;

        Transform& GetTransform();

        void Update(double deltaTime);

    private:
        // Inherited via KeyHandlerListener
        virtual void Notify(int key, int action) override;

        Transform m_transform;

        float m_fovy;
        float m_near;
        float m_far;
        float m_aspect;

        glm::vec3 m_move;

        float m_pitchAngle;
        float m_yawAngle;
    };
}

#endif // blocks_camera_h
