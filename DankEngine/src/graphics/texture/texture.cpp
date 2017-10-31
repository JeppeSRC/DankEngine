#include "texture.h"

namespace dank {

Texture::Texture() : ResourceTexture(ResourceTextureType::RESOURCE_TEXTURE_UNKNOWN, 0) ,textureID(0), width(0), height(0), deleteTexture(true) {
	GL(glGenTextures(1, &textureID));
	GL(glBindTexture(GL_TEXTURE_2D, textureID));
}

Texture::Texture(const ResourceTexture* resource) : ResourceTexture(resource) {
	GL(glGenTextures(1, &textureID));
	GL(glBindTexture(GL_TEXTURE_2D, textureID));
}

Texture::Texture(const char* filename, ResourceTextureType type) : ResourceTexture(filename, type, 0) {

}

Texture::Texture(unsigned int width, unsigned int height, unsigned int pixelSize, const void* const data, ResourceTextureType type) : ResourceTexture(width, height, pixelSize, data, type, 0) {

}

Texture::Texture(unsigned int id, unsigned int width, unsigned int height, bool deleteID) : ResourceTexture(ResourceTextureType::RESOURCE_TEXTURE_UNKNOWN, 0), textureID(id), width(width), height(height), deleteTexture(deleteID) {
	
}

Texture::Texture(unsigned int width, unsigned int height) : ResourceTexture(ResourceTextureType::RESOURCE_TEXTURE_UNKNOWN, 0), textureID(0), width(width), height(height), deleteTexture(true) {
	GL(glGenTextures(1, &textureID));
	GL(glBindTexture(GL_TEXTURE_2D, textureID));
}

Texture::~Texture() {
	if (deleteTexture) GL(glDeleteTextures(1, &textureID));
}

};
