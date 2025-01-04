#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    float yaw, pitch;
    const float SPEED = 0.01f;

public:
    Camera(const glm::vec3& pos = glm::vec3(0.0f, 3.0f, 0.0f))
        : position(pos),
        front(glm::vec3(0.0f, 0.0f, -1.0f)),
        up(glm::vec3(0.0f, 1.0f, 0.0f)),
        yaw(-90.0f),
        pitch(0.0f) {
    }

    bool isPositionValid(const glm::vec3& pos) const {
        glm::vec2 corner1(4.90363f, 7.60156f);
        glm::vec2 corner2(7.72679f, 4.68736f);
        glm::vec2 corner3(-4.28256f, -7.19005f);
        glm::vec2 corner4(-7.2052f, -4.29742f);

        glm::vec2 point(pos.x, pos.z);
        auto lineEquation = [](const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& point) {
            float a = p2.y - p1.y;
            float b = p1.x - p2.x;
            float c = p2.x * p1.y - p1.x * p2.y;
            return a * point.x + b * point.y + c;
            };

        bool side1 = lineEquation(corner1, corner2, point) >= 0;
        bool side2 = lineEquation(corner2, corner3, point) >= 0;
        bool side3 = lineEquation(corner3, corner4, point) >= 0;
        bool side4 = lineEquation(corner4, corner1, point) >= 0;

        return side1 && side2 && side3 && side4;
    }

    void processKeyboard(GLFWwindow* window, float deltaTime) {
        glm::vec3 newPos = position;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            newPos += SPEED * front;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            newPos -= SPEED * front;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            newPos -= glm::normalize(glm::cross(front, up)) * SPEED;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            newPos += glm::normalize(glm::cross(front, up)) * SPEED;

        newPos.y = 3.0f;

        //if (isPositionValid(newPos)) 
        {
            position = newPos;
        }
    }

    void processMouse(float xoffset, float yoffset, bool constrainPitch = true) {
        float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if (constrainPitch) {
            if (pitch > 89.0f) pitch = 89.0f;
            if (pitch < -89.0f) pitch = -89.0f;
        }

        glm::vec3 newFront;
        newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        newFront.y = sin(glm::radians(pitch));
        newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(newFront);
    }

    glm::mat4 getViewMatrix() const {
        return glm::lookAt(position, position + front, up);
    }

    glm::vec3 getPosition() const {
        return position;
    }
};