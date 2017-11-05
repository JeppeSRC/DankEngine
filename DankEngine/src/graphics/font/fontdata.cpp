#include "font.h"
#include <utils/asset/fileutils.h>

namespace dank {

FontManager::FontData::FontData(const ResourceFont* resource) : ResourceFont(resource) {
	switch (resource->GetStorageType()) {
		case ResourceStorageType::BINARY:
			data = resource->GetFontData();
			size = resource->GetFontDataSize();
			name = resource->GetName();
			break;
		case ResourceStorageType::FILE:
			FileUtils::ReadFile(resource->GetFilename(), (void**)&data, &size);
			name = resource->GetName();
			break;
	}
	
	ASSERT(resource->GetStorageType() == ResourceStorageType::UNKNOWN);
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

void FontManager::FontData::OnCreate(ResourceCreateState state) {
	ASSERT(state == ResourceCreateState::UNKNOWN);
	if (state != ResourceCreateState::COLD) return;
	switch (GetStorageType()) {
	case ResourceStorageType::BINARY:
		data = GetFontData();
		size = GetFontDataSize();
		name = GetName();
		break;
	case ResourceStorageType::FILE:
		FileUtils::ReadFile(GetFilename(), (void**)&data, &size);
		name = GetName();
		break;
	}
}

}