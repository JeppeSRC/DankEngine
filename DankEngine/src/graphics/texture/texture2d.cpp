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
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dankData));

	GL(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture2D::Load(unsigned int width, unsigned int height, const void* const data) {
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

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
		Load(resource->GetWidth(), resource->GetHeight(), resource->GetPixelData());
	}
}

Texture2D::Texture2D(const String& filename) : Texture(*filename, ResourceTextureType::RESOURCE_TEXTURE_TEXTURE2D) {
	Load(*filename);
	
}

Texture2D::Texture2D(const void* const data, unsigned int width, unsigned int height) : Texture(width, height, 4, data, ResourceTextureType::RESOURCE_TEXTURE_TEXTURE2D) {
	Load(width, height, data);
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
		Load(GetWidth(), GetHeight(), GetPixelData());
	}
}

}