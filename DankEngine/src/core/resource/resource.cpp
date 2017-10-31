#include "resource.h"

namespace dank {

Resource::Resource(void* data, unsigned int size, ResourceType type, ResourceStorageType storageType, unsigned int resourceID) : type(type), storageType(storageType), resourceData((unsigned long long)data), resourceDataSize(size), resourceID(resourceID) {

}

Resource::~Resource() {
	delete[] (void*)resourceData;
}


}