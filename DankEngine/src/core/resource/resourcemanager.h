#pragma once


#include <core/nativeapp.h>
#include <utils/map.h>
#include "resource.h"

namespace dank {

/*
SaveSate layout:
	- SavedStateHeader
	- ResourceEntries
	- Data
	- ID Mappings
*/

struct SavedStateHeader {
	unsigned int numResources;
	unsigned int size;
};


class ResourceManager {
private:
	List<Resource*> resources;
	Map<unsigned int, String*> idMappings;

	unsigned int resourcePointer;

public:
	ResourceManager(SavedStateHeader* savedState);
	~ResourceManager();

	void RestoreResources(ResourceCreateState state);

	void AddResource(Resource* resource);
	void AddResource(Resource* resource, unsigned int id);
	void AddResource(Resource* resource, const String& id);
	void RemoveResource(Resource* resource);
	void RemoveResource(unsigned int id);
	void RemoveResource(const String& id);

	Resource* operator[](size_t index) const;
	Resource* GetResourceByID(unsigned int id) const;
	Resource* GetResourceByID(const String& id) const;
};

}