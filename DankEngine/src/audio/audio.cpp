#include "audio.h"
#include "audiomanager.h"

namespace dank {

	Audio::Audio(String path) {
		SLEngineItf engine = AudioManager::GetEngineInterface();
		SLObjectItf outputMixObject = AudioManager::GetOutputMix();

		auto *mgr = FileUtils::assetManager;
		AAsset* asset = AAssetManager_open(mgr, path.str, AASSET_MODE_UNKNOWN);
		long start, length, fd;
		fd = AAsset_openFileDescriptor(asset, &start, &length);
		AAsset_close(asset);
		SLDataLocator_AndroidFD loc_fd = { SL_DATALOCATOR_ANDROIDFD, fd, start, length };
		SLDataFormat_MIME format_mime = { SL_DATAFORMAT_MIME, NULL, SL_CONTAINERTYPE_UNSPECIFIED };
		SLDataSource audioSrc = { &loc_fd, &format_mime };
		SLDataLocator_OutputMix loc_outmix = { SL_DATALOCATOR_OUTPUTMIX, outputMixObject };
		SLDataSink audioSnk = { &loc_outmix, NULL };

		const SLInterfaceID ids2[3] = { SL_IID_SEEK, SL_IID_MUTESOLO, SL_IID_VOLUME };
		const SLboolean req2[3] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };
		SL((*engine)->CreateAudioPlayer(engine, &playerObject, &audioSrc, &audioSnk, 3, ids2, req2));
		SL((*playerObject)->Realize(playerObject, SL_BOOLEAN_FALSE));
		SL((*playerObject)->GetInterface(playerObject, SL_IID_PLAY, &playerPlay));
		SL((*playerObject)->GetInterface(playerObject, SL_IID_SEEK, &playerSeek));
		SL((*playerObject)->GetInterface(playerObject, SL_IID_MUTESOLO, &playerMuteSolo));
		SL((*playerObject)->GetInterface(playerObject, SL_IID_VOLUME, &playerVolume));
	}


	Audio::~Audio() {
		(*playerObject)->Destroy(playerObject);
	}

}