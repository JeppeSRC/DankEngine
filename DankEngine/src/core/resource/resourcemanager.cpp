#include "resourcemanager.h"


namespace dank {

ResourceManager::ResourceManager(SavedStateHeader* savedState) {
	if (savedState) {

	}
}

ResourceManager::~ResourceManager() {

}

void ResourceManager::AddResource(Resource* resource) {
	resources.Push_back(resource);
}

void ResourceManager::RemoveResource(Resource* resource) {
	resources.Remove(resource);
}

Resource* ResourceManager::operator[](size_t index) const {
	return resources[index];
}

Resource* ResourceManager::GetResourceByID(unsigned int id) const {
	size_t size = resources.GetSize();
	for (size_t i = 0; i < size; i++) {
		Resource* res = resources[i];
		if (res->GetResourceID() == id) return res;
	}

	ASSERT_MSG(true, "No resource with ID");

	return nullptr;
}

}