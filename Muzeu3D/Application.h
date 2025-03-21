﻿#pragma once
#include "Scene.h"
#include <GLFW/glfw3.h>
#include <memory>

class Application {
private:
    GLFWwindow* window;
    std::unique_ptr<Scene> scene;

    void initWindow() {
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        if (!mode) {
            throw std::runtime_error("Failed to get video mode");
        }

        window = glfwCreateWindow(mode->width, mode->height, "Muzeul de istorie Brasov", glfwGetPrimaryMonitor(), nullptr);
        if (!window) {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }

        glfwMakeContextCurrent(window);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        if (glewInit() != GLEW_OK) {
            throw std::runtime_error("Failed to initialize GLEW");
        }

        glViewport(0, 0, mode->width, mode->height);
        glEnable(GL_DEPTH_TEST);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    static void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
        static float lastX = 600.0f, lastY = 500.0f;
        static bool firstMouse = true;

        if (firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;

        auto app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        app->scene->getCamera()->processMouse(xoffset, yoffset);
    }

public:
    Application() {
        initWindow();
        scene = std::make_unique<Scene>();
        glfwSetWindowUserPointer(window, this);
        glfwSetCursorPosCallback(window, mouseCallback);
    }

    ~Application() {
        glfwTerminate();
    }

    void run() {
        while (!glfwWindowShouldClose(window)) {
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                glfwSetWindowShouldClose(window, true);
            }

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            scene->update(window, 0.016f);
            scene->render();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
};
