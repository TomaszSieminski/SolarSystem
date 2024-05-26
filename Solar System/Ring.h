#ifndef RING_H
#define RING_H

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <string>
#include "Texture.h"

class Ring {
public:
    Ring(float innerRadius, float outerRadius, unsigned int numSides, unsigned int numRings, const std::string& texturePath);
    void draw() const;

private:
    GLuint VAO, VBO, EBO;
    Texture texture;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    void generateRing(float innerRadius, float outerRadius, unsigned int numSides, unsigned int numRings);
};

#endif
