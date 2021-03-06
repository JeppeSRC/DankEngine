#include "resource.h"

namespace dank {

ResourceFont::ResourceFont(const ResourceFont* other) : Resource((void*)other->resourceData, other->resourceDataSize, other->type, other->storageType, other->resourceID) {

}

ResourceFont::ResourceFont(const char* filename, const char* name, unsigned int resourceID) : Resource(nullptr, strlen(filename) + strlen(name) + 2, ResourceType::FONT, ResourceStorageType::FILE, resourceID) {
	unsigned char* res = denew unsigned char[resourceDataSize];

	size_t len = strlen(filename)+1;

	memcpy(res, filename, len);
	memcpy(res + len, name, resourceDataSize - len);

	resourceData = (unsigned long long)res;
}

ResourceFont::ResourceFont(const void* const data, unsigned int size, const char* name, unsigned int resourceID) : Resource(nullptr, size, ResourceType::FONT, ResourceStorageType::BINARY, resourceID) {
	unsigned int len = (unsigned int)strlen(name)+1;
	resourceDataSize += sizeof(unsigned int) + len;

	unsigned char* res = denew unsigned char[resourceDataSize];

	*(unsigned int*)res = size;

	memcpy(res + sizeof(unsigned int), name, len);
	memcpy(res + sizeof(unsigned int) + len, data, size);

	resourceData = (unsigned long long)res;
}

const char* ResourceFont::GetName() const {
	switch (storageType) {
		case ResourceStorageType::BINARY:
			return (const char*)resourceData + sizeof(unsigned int);
		case ResourceStorageType::FILE:
			return (const char*)resourceData + strlen((const char*)resourceData)+1;
	}

	ASSERT(storageType == ResourceStorageType::UNKNOWN);

	return nullptr;
}

const char* ResourceFont::GetFilename() const {
	return (const char*)resourceData;
}

const void* ResourceFont::GetFontData() const {
	const char* name = GetName();
	unsigned int len = (unsigned int)strlen(name)+1;
	
	return (const void*)(name + len);
}

unsigned int ResourceFont::GetFontDataSize() const {
	return *(unsigned int*)resourceData;
}

}