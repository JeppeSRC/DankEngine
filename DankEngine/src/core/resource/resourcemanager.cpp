#include "resourcemanager.h"


namespace dank {

ResourceManager::ResourceManager(SavedStateHeader* savedState) : resourcePointer(0) {
	if (savedState) {

	}
}

ResourceManager::~ResourceManager() {

}

void ResourceManager::RestoreResources(ResourceCreateState state) {
	size_t size = resources.GetSize();

	for (size_t i = 0; i < size; i++) {
		resources[i]->OnCreate(state);
	}
}

void ResourceManager::AddResource(Resource* resource) {
	resources.Push_back(resource);
}

void ResourceManager::AddResource(Resource* resource, unsigned int id) {
	resources.Push_back(resource);

	resource->SetID(id);
}

void ResourceManager::AddResource(Resource* resource, const String& id) {
	resources.Push_back(resource);

	unsigned int resID = resourcePointer++;

	resource->SetID(resID);

	idMappings.Add(resID, denew String(id));
}

void ResourceManager::RemoveResource(Resource* resource) {
	resources.Remove(resource);
}

void ResourceManager::RemoveResource(unsigned int id) {
	Resource* res = GetResourceByID(id);

	if (res == nullptr) {
		LOGW("No resource with ID \"%u\"", id);
		return;
	}

	RemoveResource(res);
}

void ResourceManager::RemoveResource(const String& id) {
	size_t index = idMappings.GetDataList().Find<const String&>([](String* item, const String& other) -> bool { return *item == other; }, id);

	if (index == (size_t)~0) {
		LOGW("No resource with ID \"%s\"", *id);
		return;
	}

	RemoveResource(idMappings.GetKeyList()[index]);
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

Resource* ResourceManager::GetResourceByID(const String& id) const {
	size_t index = idMappings.GetDataList().Find<const String&>([](String* item, const String& other) -> bool { return *item == other; }, id);

	if (index == (size_t)~0) {
		LOGW("No resource with ID \"%s\"", *id);
		return nullptr;
	}

	return GetResourceByID(idMappings.GetKeyList()[index]);
}

}