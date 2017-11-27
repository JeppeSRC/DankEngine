#include "audiomanager.h"
#include "application.h"
#include "utils/asset/fileutils.h"

#define JELLY_BEAN_MR1	17

namespace dank {

	SLObjectItf AudioManager::engineObject = nullptr, AudioManager::bufferQueuePlayerObject = nullptr;
	SLEngineItf AudioManager::engineInterface;

	SLObjectItf AudioManager::outputMixObject;
	SLEnvironmentalReverbItf AudioManager::outputMixInterface;

	void AudioManager::Init() {
		SL(slCreateEngine(&engineObject, 0, 0, 0, 0, 0));
		SL((*engineObject)->Realize(engineObject, SL_BOOLEAN_FALSE));
		SL((*engineObject)->GetInterface(engineObject, SL_IID_ENGINE, &engineInterface));

		SLInterfaceID ids[1] = { SL_IID_ENVIRONMENTALREVERB };
		SLboolean req[1] = { SL_BOOLEAN_FALSE };
		SL((*engineInterface)->CreateOutputMix(engineInterface, &outputMixObject, 1, ids, req));
		SL((*outputMixObject)->Realize(outputMixObject, SL_BOOLEAN_FALSE));
	}

	void AudioManager::Destroy() {
		(*outputMixObject)->Destroy(outputMixObject);
		(*engineObject)->Destroy(engineObject);
	}
}