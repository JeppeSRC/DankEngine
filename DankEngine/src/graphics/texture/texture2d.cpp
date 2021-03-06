#include "texture.h"
#include <stb_image.h>
#include <utils/log.h>
#include <utils/asset/fileutils.h>

namespace dank {

void Texture2D::Load(const unsigned char* const data, int size) {
	int x = 0;
	int y = 0;
	int c = 0;

	unsigned char* dankData = stbi_load_from_memory(data, size, &x, &y, &c, 4);

	ASSERT(dankData == nullptr);

	this->width = x;
	this->height = y;

	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

	GL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dankData));

	GL(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture2D::Load(TextureFormat format, unsigned int width, unsigned int height, const void* const data) {
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));


	switch (format) {
		case TextureFormat::R8:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
			break;
		case TextureFormat::R32F:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, width, height, 0, GL_RED, GL_FLOAT, data);
			break;
		case TextureFormat::RG8:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RG8, width, height, 0, GL_RG, GL_UNSIGNED_BYTE, data);
			break;
		case TextureFormat::RG32F:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RG32F, width, height, 0, GL_RG, GL_FLOAT, data);
			break;
		case TextureFormat::RGB8:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			break;
		case TextureFormat::RGB32F:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, data);
			break;
		case TextureFormat::RGBA8:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			break;
		case TextureFormat::RGBA32F:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, data);
			break;
	}
	
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Load(const char* filename) {
	unsigned int size = 0;
	void* data = nullptr;

	FileUtils::ReadFile(filename, &data, &size);

	Load((unsigned char*)data, size);

	delete[] data;
}

Texture2D::Texture2D(const ResourceTexture* resource) : Texture(resource) {
	ASSERT(resource->GetStorageType() == ResourceStorageType::UNKNOWN)

	if (resource->GetStorageType() == ResourceStorageType::FILE) {
		Load(resource->GetFilename());
	}
	else {
		Load(resource->GetFormat(), resource->GetWidth(), resource->GetHeight(), resource->GetPixelData());
	}
}

Texture2D::Texture2D(const String& filename) : Texture(*filename, ResourceTextureType::RESOURCE_TEXTURE_TEXTURE2D) {
	Load(*filename);
	
}

Texture2D::Texture2D(TextureFormat format, unsigned int width, unsigned int height, const void* const data) : Texture(width, height, format, data, ResourceTextureType::RESOURCE_TEXTURE_TEXTURE2D) {
	Load(format, width, height, data);
}


void Texture2D::Bind(unsigned int slot) const {
	GL(glActiveTexture(GL_TEXTURE0 + slot));
	GL(glBindTexture(GL_TEXTURE_2D, textureID));
}

void Texture2D::OnCreate(ResourceCreateState state) {
	ASSERT(state == ResourceCreateState::UNKNOWN);
	ASSERT(GetStorageType() == ResourceStorageType::UNKNOWN)

	if (GetStorageType() == ResourceStorageType::FILE) {
		Load(GetFilename());
	}
	else {
		Load(GetFormat(), GetWidth(), GetHeight(), GetPixelData());
	}
}

}