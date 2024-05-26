#include "light.h"

Light::Light(glm::vec3 pos, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec)
    : position(pos), ambient(amb), diffuse(diff), specular(spec) {}

void Light::apply(Shader& shader) {
    shader.use();
    shader.setVec3("light.position", position);
    shader.setVec3("light.ambient", ambient);
    shader.setVec3("light.diffuse", diffuse);
    shader.setVec3("light.specular", specular);
}


