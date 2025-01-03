#pragma once
#include <memory>
#include <vector>
#include "Model.h"
#include "Camera.h"
#include "Shader.h"

class Scene {
private:
    std::vector<std::shared_ptr<Model>> models;
    std::unique_ptr<Camera> camera;
    std::unique_ptr<Shader> shader;
    glm::mat4 projection;

    void initMuseum() {
        auto museum = std::make_shared<Model>("../Models/muzeu.obj", "../Models/");
        museum->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
        museum->setRotation(glm::vec3(0.0f, 45.0f, 0.0f));
        museum->setScale(glm::vec3(1.0f));
        models.push_back(museum);
    }

public:
    Scene() : camera(std::make_unique<Camera>()),
        shader(std::make_unique<Shader>("../Shaders/vertex_shader.glsl",
            "../Shaders/fragment_shader.glsl")) {
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        initMuseum();

        addModel("../Models/TV.obj", "../Models/",
            glm::vec3(-5.f, 2.70f, -6.20f),
            glm::vec3(0.0f, -130.0f, 0.0f),
            glm::vec3(0.001f));

        addModel("../Models/calaret.obj", "../Models/",
            glm::vec3(-3.f, 2.45f, -0.5f),
            glm::vec3(0.0f, 90.0f, 0.0f),
            glm::vec3(0.4f));

        addModel("../Models/old_wooden_cart.obj", "../Models/",
            glm::vec3(1.0f, 2.20f, -1.2f),
            glm::vec3(0.0f, 45.0f, 0.0f),
            glm::vec3(0.005f));

        addModel("../Models/ImageToStl.com_the_showcase.obj", "..Models/",
            glm::vec3(3.1f,2.2f,1.8f),
            glm::vec3(0.0f, 43.0f, 0.0f),
            glm::vec3(0.8f));
    }

    void addModel(const char* objPath, const char* mtlBaseDir,
        const glm::vec3& position = glm::vec3(0.0f),
        const glm::vec3& rotation = glm::vec3(0.0f),
        const glm::vec3& scale = glm::vec3(1.0f)) {
        try {
            auto model = std::make_shared<Model>(objPath, mtlBaseDir);
            model->setPosition(position);
            model->setRotation(rotation);
            model->setScale(scale);
            models.push_back(model);
            std::cout << "Loaded model: " << objPath << "\n";
        }
        catch (const std::exception& e) {
            std::cerr << "Error loading model: " << objPath << "\nException: " << e.what() << "\n";
        }

    }

    void update(GLFWwindow* window, float deltaTime) {
        camera->processKeyboard(window, deltaTime);
    }

    void render() {
        shader->use();
        shader->setMat4("projection", projection);
        shader->setMat4("view", camera->getViewMatrix());

        for (const auto& model : models) {
            shader->setMat4("model", model->getModelMatrix());
            model->draw(*shader);
        }
    }

    Camera* getCamera() { return camera.get(); }
};