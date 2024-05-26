#ifndef PLANET_H
#define PLANET_H

#include <string>
#include "Shader.h"
#include "Texture.h"
#include "Sphere.h"
#include "Ring.h"

class Planet {
public:
    Planet(const std::string& texturePath, float radius, float distance, float orbitSpeed, bool hasRings = false);
    void draw(Shader& shader);

private:
    float radius;
    float distance;
    float orbitSpeed;
    Texture texture;
    Sphere sphere;
    bool hasRings;
    Ring* ring;
};

#endif

