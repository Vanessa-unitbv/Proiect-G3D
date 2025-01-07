#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <tiny_obj_loader.h>
#include <vector>
#include <memory>
#include <unordered_map> 
#include <fstream>
#include <iostream>
#include "Mesh.h"
#include <string>

class Model {
private:
    std::vector<std::shared_ptr<Mesh>> meshes;
    glm::vec3 position{ 0.0f };
    glm::vec3 rotation{ 0.0f };
    glm::vec3 scale{ 1.0f };
    std::string name;

public:
    Model(const char* objPath, const char* mtlBaseDir) {
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string warn, err;

        if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, objPath, mtlBaseDir)) {
            throw std::runtime_error(warn + err);
        }

        std::unordered_map<std::string, std::shared_ptr<Texture>> loadedTextures;

        for (const auto& shape : shapes) {
            std::vector<GLfloat> vertices;
            std::vector<GLuint> indices;

            for (const auto& index : shape.mesh.indices) {
                // Vertex positions
                vertices.push_back(attrib.vertices[3 * index.vertex_index + 0]);
                vertices.push_back(attrib.vertices[3 * index.vertex_index + 1]);
                vertices.push_back(attrib.vertices[3 * index.vertex_index + 2]);

                // Normals
                if (index.normal_index >= 0) {
                    vertices.push_back(attrib.normals[3 * index.normal_index + 0]);
                    vertices.push_back(attrib.normals[3 * index.normal_index + 1]);
                    vertices.push_back(attrib.normals[3 * index.normal_index + 2]);
                }
                else {
                    // Add default normal if none exists
                    vertices.push_back(0.0f);
                    vertices.push_back(1.0f);
                    vertices.push_back(0.0f);
                }

                // Texture coordinates
                if (index.texcoord_index >= 0) {
                    vertices.push_back(attrib.texcoords[2 * index.texcoord_index + 0]);
                    vertices.push_back(attrib.texcoords[2 * index.texcoord_index + 1]);
                }
                else {
                    // Add default texture coordinates if none exists
                    vertices.push_back(0.0f);
                    vertices.push_back(0.0f);
                }

                indices.push_back(static_cast<GLuint>(indices.size()));
            }

            std::shared_ptr<Texture> texture;
            if (!shape.mesh.material_ids.empty() && shape.mesh.material_ids[0] >= 0) {
                const auto& material = materials[shape.mesh.material_ids[0]];
                if (!material.diffuse_texname.empty()) {
                    std::string texPath = std::string(mtlBaseDir) + material.diffuse_texname;
                    std::cout << "Attempting to load texture from: " << texPath << std::endl;

                    // Check if texture file exists
                    std::ifstream f(texPath.c_str());
                    if (!f.good()) {
                        std::cerr << "Warning: Texture file not found: " << texPath << std::endl;
                    }
                    f.close();

                    if (loadedTextures.find(texPath) == loadedTextures.end()) {
                        texture = std::make_shared<Texture>(texPath.c_str());
                        loadedTextures[texPath] = texture;
                    }
                    else {
                        texture = loadedTextures[texPath];
                    }
                }
            }

            if (!texture) {
                std::cout << "Using default texture for shape in " << objPath << std::endl;
                texture = std::make_shared<Texture>("../Textures/default.png");
            }

            meshes.push_back(std::make_shared<Mesh>(vertices, indices, texture));
        }
    }

    void draw(Shader& shader) {
        for (const auto& mesh : meshes) {
            mesh->draw(shader);
        }
    }

    void setPosition(const glm::vec3& pos) { position = pos; }
    void setRotation(const glm::vec3& rot) { rotation = rot; }
    void setScale(const glm::vec3& s) { scale = s; }

    void setName(const std::string& modelName) {  name = modelName;}
    std::string getName() const { return name;}

    glm::mat4 getModelMatrix() const {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, scale);
        return model;
    }
};