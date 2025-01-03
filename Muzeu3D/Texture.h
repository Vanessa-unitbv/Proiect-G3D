#pragma once
#include <GL/glew.h>
#include <stb_image.h>
#include <iostream>

class Texture {
private:
    GLuint textureID;

public:
    Texture(const char* path) {
        glGenTextures(1, &textureID);

        int width, height, channels;
        unsigned char* data = stbi_load(path, &width, &height, &channels, 0);

        if (data) {
            GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;  // Verificã dacã existã canal alpha
            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
        }
        else {
            std::cerr << "Failed to load texture: " << path << std::endl;
        }
    }

    ~Texture() {
        glDeleteTextures(1, &textureID);
    }

    void bind(GLuint unit = 0) {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, textureID);
    }

    GLuint getID() const { return textureID; }
};