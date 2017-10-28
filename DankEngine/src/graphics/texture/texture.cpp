#include "texture.h"

namespace dank {

Texture::Texture() : textureID(0), width(0), height(0) {
	GL(glGenTextures(1, &textureID));
	GL(glBindTexture(GL_TEXTURE_2D, textureID));
}

Texture::Texture(unsigned int width, unsigned int height) : textureID(0), width(width), height(height) {
	GL(glGenTextures(1, &textureID));
	GL(glBindTexture(GL_TEXTURE_2D, textureID));
}

Texture::~Texture() {
	GL(glDeleteTextures(1, &textureID));
}

};
