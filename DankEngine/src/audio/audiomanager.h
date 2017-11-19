#pragma once

#include <string>
#include <sstream>

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

#include <sys/system_properties.h>

#include "utils/log.h"
#include "utils/string.h"

namespace dank {

	class AudioManager {
	private:
		static SLObjectItf engineObject;
		static SLEngineItf engineInterface;

		static SLObjectItf outputMixObject;
		static SLEnvironmentalReverbItf outputMixInterface;

	public:
		static void Init();
		static void Destroy();

	private:
		inline static int ToInt(std::string string) {
			std::stringstream stream(string);
			int result;
			stream >> result;
			return result;
		}
	};

}