#include "../include/Camera.h"
#include "../include/OpenGl.h"

Camera::Camera()
    : m_position(0.0f, 50.0f, 0.0f)
    , m_front(0.0f, 0.0f, -1.0f)
    , m_up(0.0f, 1.0f, 0.0f)
    , m_yaw(-90.0f)
    , m_pitch(0.0f)
    , m_speed(10.0f)
{}

void Camera::update(float deltaTime, const Window& window) {
    // Example: basic WASD movement
    float velocity = m_speed * deltaTime;

    if (glfwGetKey(window.getNativeWindow(), GLFW_KEY_W) == GLFW_PRESS)
        m_position += m_front * velocity;
    if (glfwGetKey(window.getNativeWindow(), GLFW_KEY_S) == GLFW_PRESS)
        m_position -= m_front * velocity;
    if (glfwGetKey(window.getNativeWindow(), GLFW_KEY_A) == GLFW_PRESS)
        m_position -= glm::normalize(glm::cross(m_front, m_up)) * velocity;
    if (glfwGetKey(window.getNativeWindow(), GLFW_KEY_D) == GLFW_PRESS)
        m_position += glm::normalize(glm::cross(m_front, m_up)) * velocity;

    // Mouse look, etc. (implementation omitted for brevity)
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio) const {
    return glm::perspective(glm::radians(60.0f), aspectRatio, 0.1f, 1000.0f);
}

glm::vec3 Camera::getPosition() const {
    return m_position;
}
