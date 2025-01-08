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


    void setupLights() {
        // Room 1 - Warm light (Vlad Tepes area)
        light1 = Light(
            glm::vec3(5.0f, 4.0f, 5.0f),      // Above Vlad
            glm::vec3(0.2f, 0.15f, 0.1f),       // Warm ambient
            glm::vec3(0.8f, 0.6f, 0.4f),        // Warm diffuse
            glm::vec3(1.0f, 0.8f, 0.6f),        // Warm specular
            1.0f, 0.07f, 0.017f                  // Adjusted attenuation
        );

        // Room 2 - Cool light (Telescope area)
        light2 = Light(
            glm::vec3(-4.6f, 4.0f, -4.5f),      // Above telescope
            glm::vec3(0.1f, 0.15f, 0.2f),       // Cool ambient
            glm::vec3(0.4f, 0.6f, 0.8f),        // Cool diffuse
            glm::vec3(0.6f, 0.8f, 1.0f),        // Cool specular
            1.0f, 0.09f, 0.032f                  // Standard attenuation
        );


        // Center area - Neutral light
        light3 = Light(
            glm::vec3(0.0f, 4.0f, 0.0f),        // Higher center position
            glm::vec3(0.15f),                    // Neutral ambient
            glm::vec3(0.7f),                     // Neutral diffuse
            glm::vec3(0.9f),                     // Neutral specular
            1.0f, 0.045f, 0.0075f                // Wide-reaching attenuation
        );
    }

    unsigned int depthMapFBO;
    unsigned int depthMap;
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    std::unique_ptr<Shader> shadowMapShader;
    glm::mat4 lightSpaceMatrix;

    void initShadowMap() {
        // Creează FBO pentru depth mapping
        glGenFramebuffers(1, &depthMapFBO);

        // Creează textura pentru depth map
        glGenTextures(1, &depthMap);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
            mode->width, mode->height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

        // Atașează depth texture ca FBO's depth buffer
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void renderShadowMap() {
        // 1. Calculează light space matrix pentru shadow mapping
        glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);
        glm::mat4 lightView = glm::lookAt(
            glm::vec3(light1.position), // folosim prima lumină ca sursă principală pentru umbre
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f));
        lightSpaceMatrix = lightProjection * lightView;

        glViewport(0, 0, mode->width, mode->height);


        // 2. Randează scena din perspectiva luminii
        shadowMapShader->use();
        shadowMapShader->setMat4("lightSpaceMatrix", lightSpaceMatrix);


        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);

        for (const auto& model : models) {
            shadowMapShader->setMat4("model", model->getModelMatrix());
            model->draw(*shadowMapShader);
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }



    float rotationAngle = 0.0f; // Variabila pentru a urmări unghiul de rotație

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

    void initCavaler()
    {
        auto Cavaler = std::make_shared<Model>("../Models/Cavaler/3D_scan_armor_henry_II_of_france.obj", "../Models/Cavaler/");
        
        Cavaler->setPosition(glm::vec3(-0.2f, 2.0f, -2.2f));
        Cavaler->setRotation(glm::vec3(90.0f, 175.0f, -65.0f));
        Cavaler->setScale(glm::vec3(0.03f));
        Cavaler->setName("Cavaler");
        models.push_back(Cavaler);
    }

    void initTelescope()
    {
        auto Telescope = std::make_shared<Model>("../Models/Telescope/telescope.obj", "../Models/Telescope/");

        Telescope->setPosition(glm::vec3(-4.1f, 2.10f, -4.8f));
        Telescope->setRotation(glm::vec3(0.0f, 45.0f, 0.0f));
        Telescope->setScale(glm::vec3(0.008f));
        Telescope->setName("Telescope");
        models.push_back(Telescope);
    }

public:
    Scene() : camera(std::make_unique<Camera>()),
        shader(std::make_unique<Shader>("../Shaders/vertex_shader.glsl",
            "../Shaders/fragment_shader.glsl")),
        lightIndicatorShader(std::make_unique<Shader>("../Shaders/light_indicator_vertex.glsl",
            "../Shaders/light_indicator_fragment.glsl")),
        light1(glm::vec3(5.0f, 4.0f, 5.0f),      // Above Vlad
            glm::vec3(0.2f, 0.15f, 0.1f),       // Warm ambient
            glm::vec3(0.8f, 0.6f, 0.4f),        // Warm diffuse
            glm::vec3(1.0f, 0.8f, 0.6f)),
        light2(glm::vec3(-4.6f, 4.0f, -4.5f),      // Above telescope
            glm::vec3(0.1f, 0.15f, 0.2f),       // Cool ambient
            glm::vec3(0.4f, 0.6f, 0.8f),        // Cool diffuse
            glm::vec3(0.6f, 0.8f, 1.0f)),
        light3(glm::vec3(0.0f, 4.0f, 0.0f),        // Higher center position
            glm::vec3(0.15f),                    // Neutral ambient
            glm::vec3(0.7f),                     // Neutral diffuse
            glm::vec3(0.9f)) {

        projection = glm::perspective(glm::radians(45.0f), (float)mode->width / (float)mode->height, 0.1f, 100.0f);
        initMuseum();
        initTepes();
        initCavaler();
        initTelescope();
        setupLights();

        shadowMapShader = std::make_unique<Shader>(
            "../Shaders/shadow_map_vertex.glsl",
            "../Shaders/shadow_map_fragment.glsl"
        );
        initShadowMap();

        //ROOM 1 

        addModel("../Models/Chest/chest.obj", "../Models/Chest/",
            glm::vec3(-6.4f, 2.20f, -4.6f),
            glm::vec3(0.0f, -47.0f, 0.0f),
            glm::vec3(0.25f));

        addModel("../Models/TV/TV.obj", "../Models/TV/",
            glm::vec3(-2.7f, 3.50f, -4.5f),
            glm::vec3(0.0f, -220.0f, 0.0f),
            glm::vec3(0.001f));

        addModel("../Models/Old_Table/old_table.obj", "../Models/Old_Table/",
            glm::vec3(-2.55f, 2.20f, -4.35f),
            glm::vec3(0.0f, -45.0f, 0.0f),
            glm::vec3(1.1f));

        addModel("../Models/Camera/camera.obj", "../Models/Camera/",
            glm::vec3(-1.6f, 2.84f, -3.6f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.3f));

        addModel("../Models/Cash_Register/cash_register.obj", "../Models/Cash_Register/",
            glm::vec3(-1.2f, 3.1f, -3.1f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.001f));

        addModel("../Models/Table/table.obj", "../Models/Table/",
            glm::vec3(-1.3f, 2.20f, -3.4f),
            glm::vec3(0.0f, 130.0f, 0.0f),
            glm::vec3(0.1f));

        addModel("../Models/Medieval_Desk/medieval_desk.obj", "../Models/Medieval_Desk/",
            glm::vec3(-3.6f, 2.50f, -1.5f),
            glm::vec3(0.0f, 131.0f, 0.0f),
            glm::vec3(0.6f));

        addModel("../Models/Old_Torah_Scroll/old_torah_scroll.obj", "../Models/Old_Torah_Scroll/",
            glm::vec3(-3.65f, 2.9f, -1.45f),
            glm::vec3(0.0f, 131.0f, 0.0f),
            glm::vec3(0.06f));

        addModel("../Models/Telephone/telephone.obj", "../Models/Telephone/",
            glm::vec3(-4.6f, 3.32f, -2.6f),
            glm::vec3(0.0f, 135.0f, 0.0f),
            glm::vec3(0.24f));

        addModel("../Models/Book_Shelf/bookshelf.obj", "../Models/Book_Shelf/",
            glm::vec3(-4.8f, 3.0f, -2.7f),
            glm::vec3(0.0f, 135.0f, 0.0f),
            glm::vec3(1.6f));

        addModel("../Models/Lantern/lantern.obj", "../Models/Lantern/",
            glm::vec3(-4.9f, 3.08f, -2.9f),
            glm::vec3(0.0f, 135.0f, 0.0f),
            glm::vec3(0.2f));
       
        //ROOM 2

       /* addModel("../Models/Calaret/calaret.obj", "../Models/Calaret/",
            glm::vec3(-2.5f, 2.45f, -0.9f),
            glm::vec3(0.0f, 50.0f, 0.0f),
            glm::vec3(0.5f));

        addModel("../Models/Old_Wooden_Cart/old_wooden_cart.obj", "../Models/Old_Wooden_Cart/",
            glm::vec3(1.2f, 2.20f, -0.6f),
            glm::vec3(0.0f, 45.0f, 0.0f),
            glm::vec3(0.007f));

        addModel("../Models/Sword/sword.obj", "../Models/Sword/",
            glm::vec3(-1.7f, 2.20f, 0.5f),
            glm::vec3(0.0f, 131.0f, 0.0f),
            glm::vec3(1.0f));

        addModel("../Models/Canon/OldShipCannon.obj", "../Models/Canon/",
            glm::vec3(0.02f, 2.2f, 2.1f),
            glm::vec3(0.0f, 90.0f, 0.0f),
            glm::vec3(0.4f));*/
        
        // ROOM 3

        /*addModel("../Models/Stand/stand.obj", "../Models/Stand/",
            glm::vec3(10.15f, 2.20f,5.2f),
            glm::vec3(0.0f, 176.0f, 0.0f),
            glm::vec3(0.007f));

        addModel("../Models/Bran/model.obj", "../Models/Bran/",
            glm::vec3(4.f, 1.1f, 6.0f),
             glm::vec3(0.0f, 130.0f, 0.0f),
             glm::vec3(0.15f));

        addModel("../Models/Stema/model.obj", "../Models/Stema/",
            glm::vec3(6.22f, 2.8f, 6.27f),
            glm::vec3(0.0f, 230.0f, 0.0f),
            glm::vec3(0.02f));

        addModel("../Models/Medieval_Chest/medieval_chest.obj", "../Models/Medieval_Chest/",
            glm::vec3(2.034f, 2.40f, 4.34f),
            glm::vec3(0.0f, -45.0f, 0.0f),
            glm::vec3(0.0006f));

          addModel("../Models/Table/Table.obj", "../Models/Table/",
              glm::vec3(4.6f, 2.1f, 2.6f),
              glm::vec3(0.0f, 130.0f, 0.0f),
              glm::vec3(0.1f));

          addModel("../Models/Gun/GunMesh.obj", "../Models/Gun/",
              glm::vec3(3.841f, 2.85f, 2.5f),
              glm::vec3(0.0f, 130.0f, 0.0f),
              glm::vec3(0.001f));*/

              

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


    void render() {

        // 1. Prima trecere: generează depth map
        renderShadowMap();

        // 2. A doua trecere: randează scena normal folosind shadow mapping
        glViewport(0, 0, mode->width, mode->height);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->use();
        shader->setMat4("projection", projection);
        shader->setMat4("view", camera->getViewMatrix());
        shader->setMat4("lightSpaceMatrix", lightSpaceMatrix);
        shader->setVec3("viewPos", camera->getPosition());

        // Activează textura pentru shadow map
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        shader->setInt("shadowMap", 1);

        shader->use();
        shader->setMat4("projection", projection);
        shader->setMat4("view", camera->getViewMatrix());
        shader->setVec3("viewPos", camera->getPosition());

        if (lightEnabled) {
            for (int i = 1; i <= 3; i++) {
                const Light& light = (i == 1) ? light1 : (i == 2) ? light2 : light3;
                std::string prefix = "light" + std::to_string(i);

                shader->setVec3(prefix + ".position", light.position);
                shader->setVec3(prefix + ".ambient", light.ambient);
                shader->setVec3(prefix + ".diffuse", light.diffuse);
                shader->setVec3(prefix + ".specular", light.specular);
                shader->setFloat(prefix + ".constant", light.constant);
                shader->setFloat(prefix + ".linear", light.linear);
                shader->setFloat(prefix + ".quadratic", light.quadratic);
            }
        }
        else {
            // Ambient only lighting when disabled
            Light darkLight(
                glm::vec3(0.0f),
                glm::vec3(0.05f),
                glm::vec3(0.0f),
                glm::vec3(0.0f)
            );

            for (int i = 1; i <= 3; i++) {
                std::string prefix = "light" + std::to_string(i);
                shader->setVec3(prefix + ".position", darkLight.position);
                shader->setVec3(prefix + ".ambient", darkLight.ambient);
                shader->setVec3(prefix + ".diffuse", darkLight.diffuse);
                shader->setVec3(prefix + ".specular", darkLight.specular);
                shader->setFloat(prefix + ".constant", 1.0f);
                shader->setFloat(prefix + ".linear", 0.0f);
                shader->setFloat(prefix + ".quadratic", 0.0f);
            }
        }

        for (const auto& model : models) {
            shader->setMat4("model", model->getModelMatrix());
            model->draw(*shader);
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

        rotationAngle += 20.0f * deltaTime; // Rotește cu 20 de grade pe secundă
        if (rotationAngle >= 360.0f) {
            rotationAngle -= 360.0f; // Resetează unghiul după o rotație completă
        }

        // Aplică rotația pe modelul VladTepes
        for (auto& model : models) {
            if (model->getName() == "VladTepes" || model->getName()=="Telescope") { // Presupunem că ai o metodă `getName`
                model->setRotation(glm::vec3(0.0f, rotationAngle, 0.0f));
            }
        }
    }

    Camera* getCamera() { return camera.get(); }

    ~Scene() {
        glDeleteVertexArrays(1, &lightVAO);
        glDeleteBuffers(1, &lightVBO);
        glDeleteFramebuffers(1, &depthMapFBO);
        glDeleteTextures(1, &depthMap);
    }
};