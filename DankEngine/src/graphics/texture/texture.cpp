#include "texture.h"

namespace dank {

unsigned int Texture::GetFormatSize(TextureFormat format) {
	switch (format) {
	case TextureFormat::R8:
		return 1;
	case TextureFormat::R32F:
		return 4;
	case TextureFormat::RG8:
		return 2;
	case TextureFormat::RG32F:
		return 8;
	case TextureFormat::RGB8:
		return 3;
	case TextureFormat::RGB32F:
		return 12;
	case TextureFormat::RGBA8:
		return 4;
	case TextureFormat::RGBA32F:
		return 16;
	}

	return 0;
}

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

Texture::Texture(unsigned int width, unsigned int height, TextureFormat format, const void* const data, ResourceTextureType type) : ResourceTexture(width, height, format, data, type, 0) {

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
