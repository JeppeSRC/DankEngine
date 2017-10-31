#include "resource.h"

namespace dank {

ResourceShader::ResourceShader(const ResourceShader* other) : Resource((void*)other->resourceData, other->resourceDataSize, other->type, other->storageType, other->resourceID) {

}

ResourceShader::ResourceShader(const char* vs, const char* ps, unsigned int resourceID) : Resource(nullptr, 0, RESOURCE_SHADER, RESOURCE_STORAGE_FILE, resourceID) {
	size_t vsLen = strlen(vs)+1;
	size_t psLen = strlen(ps)+1;

	resourceDataSize = vsLen + psLen;

	void* res = denew unsigned char[resourceDataSize];

	memcpy(res, vs, vsLen);
	memcpy(res + vsLen, ps, psLen);

	resourceData = (unsigned long long)res;
}

const char* ResourceShader::GetVSCode() const {
	return (const char*)resourceData;
}

const char* ResourceShader::GetPSCode() const {
	size_t len = strlen((const char*)resourceData)+1;
	return (const char*)resourceData + len;
}

}