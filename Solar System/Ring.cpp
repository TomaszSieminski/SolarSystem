#include "Ring.h"
#include <iostream>

#define PI 3.14159265358979323846f

Ring::Ring(float innerRadius, float outerRadius, unsigned int numSides, unsigned int numRings, const std::string& texturePath)
    : texture(texturePath) {
    generateRing(innerRadius, outerRadius, numSides, numRings);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Ring::draw() const {
    glBindVertexArray(VAO);
    texture.bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Ring::generateRing(float innerRadius, float outerRadius, unsigned int numSides, unsigned int numRings) {
    float ringFactor = 2.0f * PI / numRings;
    float sideFactor = 2.0f * PI / numSides;
    float r1 = innerRadius;
    float r2 = outerRadius;
    float ringHeight = 0.02f;

    for (unsigned int ring = 0; ring <= numRings; ++ring) {
        float u = ring * ringFactor;
        float cu = cos(u);
        float su = sin(u);

        for (unsigned int side = 0; side <= numSides; ++side) {
            float v = side * sideFactor;
            float cv = cos(v);
            float sv = sin(v);
            float x = (r1 + r2 * cv) * cu;
            float y = (r1 + r2 * cv) * su;
            float z = r2 * sv * ringHeight;

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
            vertices.push_back((float)side / numSides);
            vertices.push_back((float)ring / numRings);
        }
    }

    for (unsigned int ring = 0; ring < numRings; ++ring) {
        unsigned int ringStart = ring * (numSides + 1);
        unsigned int nextRingStart = (ring + 1) * (numSides + 1);

        for (unsigned int side = 0; side < numSides; ++side) {
            unsigned int current = ringStart + side;
            unsigned int next = nextRingStart + side;

            indices.push_back(current);
            indices.push_back(next);
            indices.push_back(current + 1);

            indices.push_back(next);
            indices.push_back(next + 1);
            indices.push_back(current + 1);
        }
    }
}
