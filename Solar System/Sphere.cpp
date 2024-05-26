#include "Sphere.h"
#include <glm/glm.hpp>

#define PI 3.14159265358979323846f

Sphere::Sphere() {
    generateSphere(40, 40);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Sphere::draw() const {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Sphere::generateSphere(unsigned int latitudeBands, unsigned int longitudeBands) {
    for (unsigned int lat = 0; lat <= latitudeBands; ++lat) {
        float theta = lat * PI / latitudeBands;
        float sinTheta = sin(theta);
        float cosTheta = cos(theta);

        for (unsigned int lon = 0; lon <= longitudeBands; ++lon) {
            float phi = lon * 2 * PI / longitudeBands;
            float sinPhi = sin(phi);
            float cosPhi = cos(phi);

            float x = cosPhi * sinTheta;
            float y = cosTheta;
            float z = sinPhi * sinTheta;
            float u = 1.0f - (float(lon) / longitudeBands);
            float v = 1.0f - (float(lat) / latitudeBands);

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
            vertices.push_back(u);
            vertices.push_back(v);
            vertices.push_back(x);  // Normal x
            vertices.push_back(y);  // Normal y
            vertices.push_back(z);  // Normal z
        }
    }

    for (unsigned int lat = 0; lat < latitudeBands; ++lat) {
        for (unsigned int lon = 0; lon < longitudeBands; ++lon) {
            unsigned int first = (lat * (longitudeBands + 1)) + lon;
            unsigned int second = first + longitudeBands + 1;

            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);

            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }
}
