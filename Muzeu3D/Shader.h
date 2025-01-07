#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
private:
    GLuint programID;

    std::string loadShaderCode(const char* path) {
        std::ifstream shaderFile(path);
        if (!shaderFile.is_open()) {
            std::cerr << "Failed to load shader: " << path << std::endl;
            return "";
        }
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        return shaderStream.str();
    }

public:
    Shader(const char* vertexPath, const char* fragmentPath) {
        std::string vertexCode = loadShaderCode(vertexPath);
        std::string fragmentCode = loadShaderCode(fragmentPath);

        const char* vertexSource = vertexCode.c_str();
        const char* fragmentSource = fragmentCode.c_str();

        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSource, NULL);
        glCompileShader(vertexShader);

        GLint success;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cerr << "Vertex shader compilation failed: " << infoLog << std::endl;
        }

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cerr << "Fragment shader compilation failed: " << infoLog << std::endl;
        }

        programID = glCreateProgram();
        glAttachShader(programID, vertexShader);
        glAttachShader(programID, fragmentShader);
        glLinkProgram(programID);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    ~Shader() {
        glDeleteProgram(programID);
    }

    void use() {
        glUseProgram(programID);
    }

    void setFloat(const std::string& name, float value) {
        glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
    }

    void setMat4(const std::string& name, const glm::mat4& matrix) {
        glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void setVec3(const std::string& name, const glm::vec3& value) {
        GLint location = glGetUniformLocation(programID, name.c_str());
        if (location == -1) {
            std::cerr << "Uniform " << name << " nu a fost găsit în shader!" << std::endl;
        }
        else {
            glUniform3fv(location, 1, &value[0]);
        }
    }

    GLuint getProgram() const { return programID; }
};