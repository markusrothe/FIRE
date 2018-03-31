#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <GLFW/glfw3.h>

namespace blocks
{
    Camera::Camera(glm::vec3 const& position, float fovy, float near, float far, float viewportWidth, float viewportHeight)
        : m_transform()
        , m_fovy(fovy)
        , m_near(near)
        , m_far(far)
        , m_aspect(viewportWidth / viewportHeight)
        , m_move()
        , m_pitchAngle(0.0f)
        , m_yawAngle(0.0f)
    {
        m_transform.Translate(position);
    }

    glm::mat4 Camera::GetProjectionMatrix() const
    {
        return glm::perspective<float>(m_fovy, m_aspect, m_near, m_far);
    }

    glm::mat4 Camera::GetViewMatrix() const
    {
        auto const lookAtPoint = m_transform.GetPosition() + m_transform.GetForwardVector();
        return glm::lookAt(m_transform.GetPosition(), lookAtPoint, m_transform.GetUpVector());
    }

    Transform& Camera::GetTransform()
    {
        return m_transform;
    }

    void Camera::Notify(int key, int action)
    {
        auto const speed = 100.0f;
        if ( action == GLFW_PRESS )
        {
            switch (key)
            {
            case GLFW_KEY_W:
                m_move += speed * m_transform.GetForwardVector();
                break;
            case GLFW_KEY_S:
                m_move -= speed * m_transform.GetForwardVector();
                break;
            case GLFW_KEY_A:
                m_yawAngle = -speed;
                break;
            case GLFW_KEY_D:
                m_yawAngle = speed;
                break;
            case GLFW_KEY_Q:
                m_move += speed * m_transform.GetUpVector();
                break;
            case GLFW_KEY_E:
                m_move -= speed * m_transform.GetUpVector();
                break;
            default:
                break;
            };
        }
        else if ( action == GLFW_RELEASE)
        {
            m_move = glm::vec3();
            m_pitchAngle = 0.0f;
            m_yawAngle = 0.0f;
        }
    }

    void Camera::Update(double deltaTime)
    {
        m_transform.Translate(static_cast<float>(deltaTime) * m_move);
        m_transform.Yaw(deltaTime * m_yawAngle);
        m_transform.Pitch(deltaTime * m_pitchAngle);
    }
}
