#pragma once

#include "../include/OpenGl.h"
#include "Window.h"

class Camera {
public:
    Camera();
    ~Camera() = default;

    void update(float deltaTime, const Window& window);
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix(float aspectRatio) const;
    glm::vec3 getPosition() const;

private:
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    float m_yaw;
    float m_pitch;
    float m_speed;
};
