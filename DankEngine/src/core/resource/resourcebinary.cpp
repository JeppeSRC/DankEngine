#include "resource.h"

namespace dank {


ResourceBinary::ResourceBinary(void* const data, unsigned int size, ResourceStorageType storageType, unsigned int resourceID) : Resource(data, size, ResourceType::BINARY, ResourceStorageType::BINARY, resourceID) {

}

ResourceBinary::~ResourceBinary() {

}

}