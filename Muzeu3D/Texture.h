#pragma once
#include <GL/glew.h>
#include <stb_image.h>
#include <iostream>
#include <stdexcept>

class Texture {
private:
    GLuint textureID;

public:
    Texture(const char* path) {
        glGenTextures(1, &textureID);

        stbi_set_flip_vertically_on_load(true);

        int width, height, channels;
        unsigned char* data = stbi_load(path, &width, &height, &channels, 0);

        if (data) {
            GLenum format;
            if (channels == 1)
                format = GL_RED;
            else if (channels == 3)
                format = GL_RGB;
            else if (channels == 4)
                format = GL_RGBA;
            else {
                stbi_image_free(data);
                throw std::runtime_error("Unsupported number of channels");
            }

            glBindTexture(GL_TEXTURE_2D, textureID);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            float maxAniso = 0.0f;
            glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAniso);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAniso);

            stbi_image_free(data);
        }
        else {
            throw std::runtime_error(std::string("Failed to load texture: ") + path);
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