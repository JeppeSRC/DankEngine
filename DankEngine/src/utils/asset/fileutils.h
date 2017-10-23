#pragma once
#include <android/asset_manager.h>
#include "utils/string.h"
#include "utils/log.h"
#include "utils/memory/memory.h"

namespace dank {

	class FileUtils {
	public:
		static AAssetManager* assetManager;

		static void ReadFile(const char* const path, void** data, unsigned int* size);
		static String ReadTextFile(const char* const path);

		static void PrintFiles(const char* const path);
	};

}
