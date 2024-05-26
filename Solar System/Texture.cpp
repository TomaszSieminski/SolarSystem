#include "Texture.h"
#include <iostream>
#include <SOIL2/SOIL2.h>

Texture::Texture() : ID(0), texturePath("") {}

Texture::Texture(const std::string& path) : texturePath(path) {
    loadTexture();
}

void Texture::loadTexture() {
    ID = SOIL_load_OGL_texture(texturePath.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
    if (ID == 0) {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
    }
}

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, ID);
}


