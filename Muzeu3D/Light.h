    #pragma once
    #include <glm/glm.hpp>

    struct Light {
        glm::vec3 position;
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        float constant;
        float linear;
        float quadratic;

        Light(glm::vec3 pos = glm::vec3(0.0f),
            glm::vec3 amb = glm::vec3(0.1f),
            glm::vec3 diff = glm::vec3(0.5f),
            glm::vec3 spec = glm::vec3(1.0f),
            float cons = 1.0f,
            float lin = 0.09f,
            float quad = 0.032f)
            : position(pos), ambient(amb), diffuse(diff), specular(spec),
            constant(cons), linear(lin), quadratic(quad) {
        }
    };