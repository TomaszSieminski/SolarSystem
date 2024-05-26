#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <glad/glad.h>

class Texture {
public:
    GLuint ID;
    std::string texturePath;

    Texture();
    Texture(const std::string& path);
    void loadTexture();
    void bind() const;
};

#endif
