#include "font.h"
#include <utils/asset/fileutils.h>

namespace dank {

FontManager::FontData::FontData(const ResourceFont* resource) : ResourceFont(resource) {
	switch (resource->GetStorageType()) {
		case ResourceStorageType::RESOURCE_STORAGE_BINARY:
			data = resource->GetFontData();
			size = resource->GetFontDataSize();
			name = resource->GetName();
			break;
		case ResourceStorageType::RESOURCE_STORAGE_FILE:
			FileUtils::ReadFile(resource->GetFilename(), (void**)&data, &size);
			name = resource->GetName();
			break;
	}
	
	ASSERT(resource->GetStorageType() == ResourceStorageType::RESOURCE_STORAGE_UNKNOWN);
}

FontManager::FontData::FontData(const void* const data, unsigned int size, const String& name) : ResourceFont(data, size, *name, 0), name(name), data(data), size(size) {

}

FontManager::FontData::FontData(const String& filename, const String& name) : ResourceFont(*filename, *name, 0), name(name) {

	FileUtils::ReadFile(*filename, (void**)&data, &size);

	ASSERT(data == nullptr);
}

FontManager::FontData::~FontData() {
	delete[] data;
}

}