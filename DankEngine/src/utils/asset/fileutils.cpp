#include "fileutils.h"

namespace dank {

	AAssetManager* FileUtils::assetManager = nullptr;

	void FileUtils::ReadFile(const char* const path, void** data, unsigned int* size) {
		AAsset* asset = AAssetManager_open(assetManager, path, AASSET_MODE_UNKNOWN);

		if (!asset) {
			LOGD("[FileUtils] File: %s doesn't exist! U nub!!!!!!!", path);
			*data = nullptr;
			*size = 0;
			return;
		}

		*size = AAsset_getLength(asset);

		*data = denew unsigned char[*size];

		AAsset_read(asset, *data, *size);
		AAsset_close(asset);
	}

	String FileUtils::ReadTextFile(const char* const path) {
		unsigned int size = 0;
		void* data = nullptr;

		ReadFile(path, &data, &size);

		if (!data) return "";

		return String((char*)data, size);
	}

	void FileUtils::PrintFiles(const char* const path) {

		AAssetDir* dir = AAssetManager_openDir(assetManager, path);

		const char* file = nullptr;

		LOGD("[FileUtils] PrintingFiles in %s", path);
		unsigned int index = 0;
		while (file = AAssetDir_getNextFileName(dir)) {
			LOGD("[FileUtils] File %u at %s", index++, file);
		}

		AAssetDir_close(dir);

	}

}