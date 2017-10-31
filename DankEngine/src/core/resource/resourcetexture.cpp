#include "resource.h"

namespace dank {


ResourceTexture::ResourceTexture(const ResourceTexture* other) : Resource((void*)other->resourceData, other->resourceDataSize, other->type, other->storageType, other->resourceID), textureType(other->textureType) {

}

ResourceTexture::ResourceTexture(ResourceTextureType type, unsigned int resourceID) : Resource(nullptr, 0, ResourceType::RESOURCE_TEXTURE, ResourceStorageType::RESOURCE_STORAGE_UNKNOWN, resourceID), textureType(type) { }


ResourceTexture::ResourceTexture(const char* filename, ResourceTextureType type, unsigned int resourceID) : Resource(nullptr, strlen(filename) + 1, ResourceType::RESOURCE_TEXTURE, ResourceStorageType::RESOURCE_STORAGE_FILE, resourceID), textureType(type) {
	void* res = denew unsigned char[resourceDataSize];

	memcpy(res, filename, resourceDataSize);

	resourceData = (unsigned long long)res;
}

ResourceTexture::ResourceTexture(unsigned int width, unsigned int height, unsigned int pixelSize, const void* const data, ResourceTextureType type, unsigned int resourceID) : Resource(nullptr, 0, ResourceType::RESOURCE_TEXTURE, ResourceStorageType::RESOURCE_STORAGE_BINARY, resourceID), textureType(type) {
	resourceDataSize = width * height * pixelSize + 12;

	void* res = denew unsigned char[resourceDataSize];
	unsigned int* tmp = (unsigned int*)res;

	tmp[0] = width;
	tmp[1] = height;
	tmp[2] = pixelSize;

	memcpy(&tmp[3], data, resourceDataSize - 12);


	resourceData = (unsigned long long)res;
}

const char* ResourceTexture::GetFilename() const {
	return (const char*)resourceData;
}

unsigned int ResourceTexture::GetWidth() const {
	return *(unsigned int*)resourceData;
}

unsigned int ResourceTexture::GetHeight() const {
	return *(unsigned int*)resourceData + 4;
}

unsigned int ResourceTexture::GetPixelSize() const {
	return *(unsigned int*)resourceData + 8;
}

const void* ResourceTexture::GetPixelData() const {
	return (const void*)((const unsigned int*)resourceData + 3);
}

}