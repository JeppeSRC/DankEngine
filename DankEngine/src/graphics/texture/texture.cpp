#include "texture.h"

namespace dank {

Texture::Texture() : textureID(0), width(0), height(0), deleteTexture(true) {
	GL(glGenTextures(1, &textureID));
	GL(glBindTexture(GL_TEXTURE_2D, textureID));
}

Texture::Texture(unsigned int id, unsigned int width, unsigned int height, bool deleteID) : textureID(id), width(width), height(height), deleteTexture(deleteID) {
	
}

Texture::Texture(unsigned int width, unsigned int height) : textureID(0), width(width), height(height), deleteTexture(true) {
	GL(glGenTextures(1, &textureID));
	GL(glBindTexture(GL_TEXTURE_2D, textureID));
}

Texture::~Texture() {
	if (deleteTexture) GL(glDeleteTextures(1, &textureID));
}

};
