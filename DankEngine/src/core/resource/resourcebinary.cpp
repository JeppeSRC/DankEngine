#include "resource.h"

namespace dank {


ResourceBinary::ResourceBinary(void* const data, unsigned int size, ResourceStorageType storageType, unsigned int resourceID) : Resource(data, size, RESOURCE_BINARY, RESOURCE_STORAGE_BINARY, resourceID) {

}

ResourceBinary::~ResourceBinary() {

}

}