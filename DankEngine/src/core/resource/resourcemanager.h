#pragma once


#include <core/nativeapp.h>
#include <utils/list.h>
#include "resource.h"

namespace dank {

/*
SaveSate layout:
	- SavedStateHeader
	- ResourceEntries
	- Data
*/

struct SavedStateHeader {
	unsigned int numResources;
	unsigned int size;
};


class ResourceManager {
private:
	List<Resource*> resources;

public:
	ResourceManager(SavedStateHeader* savedState);
	~ResourceManager();

	void AddResource(Resource* resource);
	void RemoveResource(Resource* resource);
};

}