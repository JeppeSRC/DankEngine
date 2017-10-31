#include "resource.h"

namespace dank {

ResourceFont::ResourceFont(const ResourceFont* other) : Resource((void*)other->resourceData, other->resourceDataSize, other->type, other->storageType, other->resourceID) {

}

ResourceFont::ResourceFont(const char* filename, const char* name, unsigned int resourceID) : Resource(nullptr, strlen(filename) + strlen(name) + 2, RESOURCE_FONT, RESOURCE_STORAGE_FILE, resourceID) {
	void* res = denew unsigned char[resourceDataSize];

	size_t len = strlen(filename)+1;

	memcpy(res, filename, len);
	memcpy(res + len, name, resourceDataSize - len);

	resourceData = (unsigned long long)res;
}

ResourceFont::ResourceFont(const void* const data, unsigned int size, const char* name, unsigned int resourceID) : Resource(nullptr, size, RESOURCE_FONT, RESOURCE_STORAGE_BINARY, resourceID) {
	unsigned int len = (unsigned int)strlen(name)+1;
	resourceDataSize += sizeof(unsigned int) + len;

	void* res = denew unsigned char[resourceDataSize];

	*(unsigned int*)res = size;

	memcpy(res + sizeof(unsigned int), name, len);
	memcpy(res + sizeof(unsigned int) + len, data, size);

	resourceData = (unsigned long long)res;
}

const char* ResourceFont::GetName() const {
	switch (storageType) {
		case RESOURCE_STORAGE_BINARY:
			return (const char*)resourceData + sizeof(unsigned int);
		case RESOURCE_STORAGE_FILE:
			return (const char*)resourceData + strlen((const char*)resourceData)+1;
	}

	ASSERT(storageType == RESOURCE_STORAGE_UNKNOWN);

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