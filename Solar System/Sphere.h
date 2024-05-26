#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include <glad/glad.h>

class Sphere {
public:
    Sphere();
    void draw() const;

private:
    GLuint VAO, VBO, EBO;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    void generateSphere(unsigned int latitudeBands, unsigned int longitudeBands);
};

#endif
