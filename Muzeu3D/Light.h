#include <glm/glm.hpp>
#include <GL/glew.h>

class Light {
public:
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    Light(glm::vec3 pos, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec)
        : position(pos), ambient(amb), diffuse(diff), specular(spec) {}

    void sendToShader(GLuint shaderProgram) {
        glUniform3fv(glGetUniformLocation(shaderProgram, "light.position"), 1, &position[0]);
        glUniform3fv(glGetUniformLocation(shaderProgram, "light.ambient"), 1, &ambient[0]);
        glUniform3fv(glGetUniformLocation(shaderProgram, "light.diffuse"), 1, &diffuse[0]);
        glUniform3fv(glGetUniformLocation(shaderProgram, "light.specular"), 1, &specular[0]);
    }
};
