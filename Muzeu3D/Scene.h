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

        addModel("../Models/TV/TV.obj", "../Models/TV/",
            glm::vec3(-5.f, 2.70f, -6.20f),
            glm::vec3(0.0f, -130.0f, 0.0f),
            glm::vec3(0.001f));

        addModel("../Models/Calaret/calaret.obj", "../Models/Calaret/",
            glm::vec3(-3.f, 2.45f, -0.5f),
            glm::vec3(0.0f, 90.0f, 0.0f),
            glm::vec3(0.4f));

        addModel("../Models/Old_Wooden_Cart/old_wooden_cart.obj", "../Models/Old_Wooden_Cart/",
            glm::vec3(1.0f, 2.20f, -1.2f),
            glm::vec3(0.0f, 45.0f, 0.0f),
            glm::vec3(0.005f));

        addModel("../Models/Chest/chest.obj", "../Models/Chest/",
            glm::vec3(-5.f, 2.70f, -4.20f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.1f));

        addModel("../Models/Vikings_Weapons/vikings_weapons.obj", "../Models/Vikings_Weapons/",
            glm::vec3(-5.f, 2.70f, -3.20f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(1.f));

        addModel("../Models/Medieval_Desk/medieval_desk.obj", "../Models/Medieval_Desk/",
            glm::vec3(-3.f, 2.70f, -2.20f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(1.f));
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