#include "Planet.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Planet::Planet(const std::string& texturePath, float radius, float distance, float orbitSpeed, bool hasRings)
    : radius(radius), distance(distance), orbitSpeed(orbitSpeed), texture(texturePath), sphere(), hasRings(hasRings) {
    if (hasRings) {
        ring = new Ring(radius * 2.5f, radius * 0.5f, 64, 64, "textures/saturn_ring.png");
    }
    else {
        ring = nullptr;
    }
}

void Planet::draw(Shader& shader) {
    float time = static_cast<float>(glfwGetTime());
    float angle = time * orbitSpeed;

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(distance * cos(angle), 0.0f, distance * sin(angle)));
    model = glm::scale(model, glm::vec3(radius));
    model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    shader.setMat4("model", model);

    texture.bind();
    sphere.draw();

    if (hasRings) {
        glm::mat4 ringModel = model;
        ringModel = glm::rotate(ringModel, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        shader.setMat4("model", ringModel);
        ring->draw();
    }
}



