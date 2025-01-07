#pragma once
#include <memory>
#include <vector>
#include "Model.h"
#include "Camera.h"
#include "Shader.h"
#include "Light.h"

class Scene {
private:
    std::vector<std::shared_ptr<Model>> models;
    std::unique_ptr<Camera> camera;
    std::unique_ptr<Shader> shader;
    std::unique_ptr<Shader> lightIndicatorShader;
    unsigned int lightVAO, lightVBO;
    glm::mat4 projection;

    Light light1;
    Light light2;
    Light light3;

    bool lightEnabled = true;

    float vladRotationAngle = 0.0f; // Variabila pentru a urmări unghiul de rotație

    void initMuseum() {
        auto museum = std::make_shared<Model>("../Models/muzeu.obj", "../Models/");
        museum->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
        museum->setRotation(glm::vec3(0.0f, 45.0f, 0.0f));
        museum->setScale(glm::vec3(1.0f));
        models.push_back(museum);
    }
    void initTepes() {
        auto VladTepes = std::make_shared<Model>("../Models/VladTepes/vlad_tepes.obj", "../Models/VladTepes/");
        VladTepes->setPosition(glm::vec3(6.69f, 3.65f, 4.95f));
        VladTepes->setRotation(glm::vec3(0.0f, 176.0f, 0.0f));
        VladTepes->setScale(glm::vec3(0.0007f));
        VladTepes->setName("VladTepes");
        models.push_back(VladTepes);
    }

public:
    Scene() : camera(std::make_unique<Camera>()),
        shader(std::make_unique<Shader>("../Shaders/vertex_shader.glsl",
            "../Shaders/fragment_shader.glsl")),
        lightIndicatorShader(std::make_unique<Shader>("../Shaders/light_indicator_vertex.glsl",
            "../Shaders/light_indicator_fragment.glsl")),
        light1(glm::vec3(4.3f, 4.0f, 4.2f),
            glm::vec3(0.1f, 0.1f, 0.1f),
            glm::vec3(2.0f, 2.0f, 2.0f),
            glm::vec3(2.0f, 2.0f, 2.0f)),
        light2(glm::vec3(-4.3f, 4.0f, -4.2f),
            glm::vec3(0.1f, 0.1f, 0.1f),
            glm::vec3(2.0f, 2.0f, 2.0f),
            glm::vec3(2.0f, 2.0f, 2.0f)),
        light3(glm::vec3(0.0f, 4.0f, 0.0f),
            glm::vec3(0.1f, 0.1f, 0.1f),
            glm::vec3(2.0f, 2.0f, 2.0f),
            glm::vec3(2.0f, 2.0f, 2.0f)) {

        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        initMuseum();
        initTepes();

        addModel("../Models/TV/TV.obj", "../Models/TV/",
            glm::vec3(-5.1f, 3.50f, -6.0f),
            glm::vec3(0.0f, -130.0f, 0.0f),
            glm::vec3(0.001f));

        addModel("../Models/Calaret/calaret.obj", "../Models/Calaret/",
            glm::vec3(-2.5f, 2.45f, -0.9f),
            glm::vec3(0.0f, 50.0f, 0.0f),
            glm::vec3(0.5f));

        addModel("../Models/Old_Wooden_Cart/old_wooden_cart.obj", "../Models/Old_Wooden_Cart/",
            glm::vec3(1.2f, 2.20f, -0.6f),
            glm::vec3(0.0f, 45.0f, 0.0f),
            glm::vec3(0.007f));

        addModel("../Models/Chest/chest.obj", "../Models/Chest/",
            glm::vec3(-6.4f, 2.20f, -4.6f),
            glm::vec3(0.0f, -47.0f, 0.0f),
           glm::vec3(0.25f));

        addModel("../Models/Medieval_Desk/medieval_desk.obj", "../Models/Medieval_Desk/",
            glm::vec3(-3.6f, 2.50f, -1.5f),
            glm::vec3(0.0f, 131.0f, 0.0f),
            glm::vec3(0.6f));

        addModel("../Models/Old_Torah_Scroll/old_torah_scroll.obj", "../Models/Old_Torah_Scroll/",
            glm::vec3(-3.65f, 2.9f,-1.45f),
            glm::vec3(0.0f, 131.0f, 0.0f),
            glm::vec3(0.06f));

        addModel("../Models/Stand/stand.obj", "../Models/Stand/",
            glm::vec3(10.2f, 2.20f,5.2f),
            glm::vec3(0.0f, 176.0f, 0.0f),
            glm::vec3(0.007f));

        addModel("../Models/Sword/sword.obj", "../Models/Sword/",
            glm::vec3(-1.7f, 2.20f, 0.5f),
            glm::vec3(0.0f, 131.0f, 0.0f),
            glm::vec3(1.0f));

        /*addModel("../Models/Camera/camera.obj", "../Models/Camera/",
            glm::vec3(-1.8f, 2.84f, -3.9f),
            glm::vec3(0.0f, -30.0f, 0.0f),
            glm::vec3(0.002f));*/

        addModel("../Models/Cash_Register/cash_register.obj", "../Models/Cash_Register/",
            glm::vec3(-1.2f, 3.1f, -3.1f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.001f));

        addModel("../Models/Table/table.obj", "../Models/Table/",
            glm::vec3(-1.3f, 2.20f, -3.4f),
            glm::vec3(0.0f, 130.0f, 0.0f),
            glm::vec3(0.1f));

        addModel("../Models/Bran/model.obj", "../Models/Bran/",
            glm::vec3(4.64f, 1.49f, 6.4f),
             glm::vec3(0.0f, 180.0f, 0.0f),
             glm::vec3(0.1f));

        addModel("../Models/Old_Table/old_table.obj", "../Models/Old_Table/",
            glm::vec3(-5.f, 2.20f, -6.20f),
            glm::vec3(0.0f, 45.0f, 0.0f),
            glm::vec3(1.1f));

        addModel("../Models/Cupboard/cupboard.obj", "../Models/Cupboard/",
            glm::vec3(-2.5f, 2.70f, -5.20f),
            glm::vec3(0.0f, -45.0f, 0.0f),
            glm::vec3(0.003f));

        addModel("../Models/Stema/model.obj", "../Models/Stema/",
            glm::vec3(6.22f, 2.8f, 6.27f),
            glm::vec3(0.0f, 230.0f, 0.0f),
            glm::vec3(0.02f));

        addModel("../Models/Telephone/telephone.obj", "../Models/Telephone/",
            glm::vec3(-4.4f, 3.32f, -2.4f),
            glm::vec3(0.0f, 135.0f, 0.0f),
            glm::vec3(0.24f));

        addModel("../Models/Book_Shelf/bookshelf.obj", "../Models/Book_Shelf/",
            glm::vec3(-4.6f, 3.0f, -2.50f),
            glm::vec3(0.0f, 135.0f, 0.0f),
            glm::vec3(1.6f));

        addModel("../Models/Lantern/lantern.obj", "../Models/Lantern/",
            glm::vec3(-4.7f, 3.08f, -2.7f),
            glm::vec3(0.0f, 135.0f, 0.0f),
            glm::vec3(0.2f));

        addModel("../Models/Lamp/lamp.obj", "../Models/Lamp/",
            glm::vec3(-3.95f, 3.50f, -1.15f),
            glm::vec3(0.0f, 131.0f, 0.0f),
            glm::vec3(0.3f));

        addModel("../Models/Medieval_Chest/medieval_chest.obj", "../Models/Medieval_Chest/",
            glm::vec3(2.034f, 2.40f, 4.34f),
            glm::vec3(0.0f, -45.0f, 0.0f),
            glm::vec3(0.0006f));

        addModel("../Models/Cavaler/3D_scan_armor_henry_II_of_france.obj", "../Models/Cavaler/",
            glm::vec3(0.57f, 2.0f, 2.88f),
            glm::vec3(90.0f, 175.0f, 45.0f),
            glm::vec3(0.03f));

        addModel("../Models/Canon/OldShipCannon.obj", "../Models/Canon/",
            glm::vec3(0.015f, 2.2f, 2.02f),
            glm::vec3(0.0f, 90.0f, 0.0f),
            glm::vec3(0.4f));

          addModel("../Models/Table/Table.obj", "../Models/Table/",
              glm::vec3(4.6f, 2.1f, 2.6f),
              glm::vec3(0.0f, 130.0f, 0.0f),
              glm::vec3(0.1f));

          addModel("../Models/Gun/GunMesh.obj", "../Models/Gun/",
              glm::vec3(3.841f, 2.85f, 2.5f),
              glm::vec3(0.0f, 130.0f, 0.0f),
              glm::vec3(0.001f));

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

        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
            lightEnabled = true;
        }
        if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
            lightEnabled = false;
        }

        vladRotationAngle += 50.0f * deltaTime; // Rotește cu 50 de grade pe secundă
        if (vladRotationAngle >= 360.0f) {
            vladRotationAngle -= 360.0f; // Resetează unghiul după o rotație completă
        }

        // Aplică rotația pe modelul VladTepes
        for (auto& model : models) {
            if (model->getName() == "VladTepes") { // Presupunem că ai o metodă `getName`
                model->setRotation(glm::vec3(0.0f, vladRotationAngle, 0.0f));
            }
        }
    }

    void render() {
        shader->use();
        shader->setMat4("projection", projection);
        shader->setMat4("view", camera->getViewMatrix());

        if (lightEnabled) {
            shader->setVec3("light1.position", light1.position);
            shader->setVec3("light1.ambient", glm::vec3(0.4f, 0.4f, 0.4f));
            shader->setVec3("light1.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
            shader->setVec3("light1.specular", glm::vec3(0.5f, 0.5f, 0.5f));

            shader->setVec3("light2.position", light2.position);
            shader->setVec3("light2.ambient", glm::vec3(0.4f, 0.4f, 0.4f));
            shader->setVec3("light2.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
            shader->setVec3("light2.specular", glm::vec3(0.5f, 0.5f, 0.5f));

            shader->setVec3("light3.position", light3.position);
            shader->setVec3("light3.ambient", glm::vec3(0.4f, 0.4f, 0.4f));
            shader->setVec3("light3.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
            shader->setVec3("light3.specular", glm::vec3(0.5f, 0.5f, 0.5f));

        }
        else {
            shader->setVec3("light1.position", glm::vec3(1.0f, 1.0f, 1.0f));
            shader->setVec3("light1.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
            shader->setVec3("light1.diffuse", glm::vec3(0.1f, 0.1f, 0.1f));
            shader->setVec3("light1.specular", glm::vec3(0.1f, 0.1f, 0.1f));

            shader->setVec3("light2.position", glm::vec3(1.0f, 1.0f, 1.0f));
            shader->setVec3("light2.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
            shader->setVec3("light2.diffuse", glm::vec3(0.1f, 0.1f, 0.1f));
            shader->setVec3("light2.specular", glm::vec3(0.1f, 0.1f, 0.1f));

            shader->setVec3("light3.position", glm::vec3(1.0f, 1.0f, 1.0f));
            shader->setVec3("light3.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
            shader->setVec3("light3.diffuse", glm::vec3(0.1f, 0.1f, 0.1f));
            shader->setVec3("light3.specular", glm::vec3(0.1f, 0.1f, 0.1f));

        }

        // Draw scene models
        for (const auto& model : models) {
            shader->setMat4("model", model->getModelMatrix());
            model->draw(*shader);
        }
    }

    Camera* getCamera() { return camera.get(); }

    ~Scene() {
        glDeleteVertexArrays(1, &lightVAO);
        glDeleteBuffers(1, &lightVBO);
    }
};