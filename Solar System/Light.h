#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include "Shader.h"

class Light {
public:
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    Light(glm::vec3 pos, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec);

    void apply(Shader& shader);
};

#endif
