#pragma once
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera {
public:
    // Constants
    static constexpr float YAW = -90.0f;
    static constexpr float PITCH = 0.0f;
    static constexpr float SPEED = 2.5f;
    static constexpr float SENSITIVITY = 0.1f;

    // Camera attributes
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    // Euler Angles
    float yaw;
    float pitch;

    // Options
    float movementSpeed;
    float mouseSensitivity;

    // Constructor
    // Header
    Camera(glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f),
        glm::vec3 up = glm::vec3(0.0f,1.0f,0.0f),
        float yaw = YAW,
        float pitch = PITCH);


    // Methods
    glm::mat4 GetViewMatrix() const;
    void ProcessKeyboard(CameraMovement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

private:
    void updateCameraVectors();
};

