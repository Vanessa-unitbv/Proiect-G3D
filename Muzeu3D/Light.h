#include <glm/glm.hpp>
#include <GL/glew.h>

class Light {
public:
    glm::vec3 position;   // Poziția luminii
    glm::vec3 ambient;    // Componenta ambientală a luminii
    glm::vec3 diffuse;    // Componenta difuză a luminii
    glm::vec3 specular;   // Componenta speculară a luminii

    // Constructor pentru setarea valorilor luminii
    Light(glm::vec3 pos, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec)
        : position(pos), ambient(amb), diffuse(diff), specular(spec) {}

    // Metodă pentru a trimite datele luminii la shader
    void sendToShader(GLuint shaderID) {
        // Trimite poziția luminii
        glUniform3fv(glGetUniformLocation(shaderID, "light.position"), 1, &position[0]);

        // Trimite componentele luminii (ambient, difuză, speculară)
        glUniform3fv(glGetUniformLocation(shaderID, "light.ambient"), 1, &ambient[0]);
        glUniform3fv(glGetUniformLocation(shaderID, "light.diffuse"), 1, &diffuse[0]);
        glUniform3fv(glGetUniformLocation(shaderID, "light.specular"), 1, &specular[0]);
    }
};
