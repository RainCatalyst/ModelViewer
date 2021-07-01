#ifndef COMPUTE_COLORS_H
#define COMPUTE_COLORS_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glad/glad.h> // holds all OpenGL type declarations
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>
#include <iostream>
#include "rendering/Mesh.h"
#include <random>

float get_random()
{
    static std::default_random_engine e;
    static std::uniform_real_distribution<> dis(0, 1); // range 0 - 1
    return dis(e);
}

glm::vec3 computeNormal(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3){
    glm::vec3 vec12 = point2 - point1;
    glm::vec3 vec13 = point3 - point1;

    return glm::normalize(glm::cross(point2 - point1, point3 - point1));
}


void computeMeshColors(Mesh& mesh){
    std::cout << "Computing mesh colors..." << std::endl;
    std::cout << "Vertex count: " << mesh.vertices.size() << std::endl;
    std::cout << "Index count: " << mesh.indices.size() << std::endl;
    glm::vec3 z_axis(0.0f, 1.0f, 0.0f);

    for (int i = 0; i < mesh.indices.size(); i+=3){
        // Assuming triangular mesh
        unsigned int index0 = mesh.indices[i];
        unsigned int index1 = mesh.indices[i + 1];
        unsigned int index2 = mesh.indices[i + 2];
        glm::vec3 face_normal = computeNormal(mesh.vertices[index0].Position, mesh.vertices[index1].Position, mesh.vertices[index2].Position);
        float angle_rad = glm::acos(glm::dot(face_normal, z_axis));
        float angle_norm = angle_rad / glm::pi<float>();
        mesh.vertices[index0].TexCoords = {angle_norm, 0.0f};
        mesh.vertices[index1].TexCoords = {angle_norm, 0.0f};
        mesh.vertices[index2].TexCoords = {angle_norm, 0.0f};
    }
    std::cout << "Done." << std::endl;
}

void normalizeModel(Model* model){
    glm::vec3 min = glm::vec3(1e10f);
    glm::vec3 max = glm::vec3(1e-10f);
   
    for (int i = 0; i < model->meshes.size(); i++){
        for (int j = 0; j < model->meshes[i].vertices.size(); j++){
            Vertex vertex = model->meshes[i].vertices[j];
            if (vertex.Position.x < min.x)
                min.x = vertex.Position.x;
            else if (vertex.Position.x > max.x)
                max.x = vertex.Position.x;
            if (vertex.Position.y < min.y)
                min.y = vertex.Position.y;
            else if (vertex.Position.y > max.y)
                max.y = vertex.Position.y;
            if (vertex.Position.z < min.z)
                min.z = vertex.Position.z;
            else if (vertex.Position.z > max.z)
                max.z = vertex.Position.z;
        }
    }

    glm::vec3 size = max - min;
    glm::vec3 center = (min + max) * 0.5f;
    float max_size = glm::max(size.x, size.y);
    max_size = glm::max(max_size, size.z);

    for (int i = 0; i < model->meshes.size(); i++){
        for (int j = 0; j < model->meshes[i].vertices.size(); j++){
            model->meshes[i].vertices[j].Position = (model->meshes[i].vertices[j].Position - center) / max_size;
        }
    }

    std::cout << "BBox size: " << glm::to_string(size) << " (max = " << max_size << ")" << std::endl;
    std::cout << "BBox center: " << glm::to_string(center) << std::endl;
}

void computeModelColors(Model* model){
    for (int i = 0; i < model->meshes.size(); i++){
        computeMeshColors(model->meshes.at(i));
    }
}

#endif