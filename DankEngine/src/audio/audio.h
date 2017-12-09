#pragma once

#include "utils/string.h"
#include "utils/log.h"
#include "utils/asset/fileutils.h"

namespace dank {

	class Audio {
	private:
		SLObjectItf playerObject;
		SLPlayItf playerPlay;
		SLSeekItf playerSeek;
		SLMuteSoloItf playerMuteSolo;
		SLVolumeItf playerVolume;

	public:
		Audio(String path);
		~Audio();

		inline void Play() { SL((*playerPlay)->SetPlayState(playerPlay, SL_PLAYSTATE_PLAYING)); }
		inline void Pause() { SL((*playerPlay)->SetPlayState(playerPlay, SL_PLAYSTATE_PAUSED)); }
		inline void Stop() { SL((*playerPlay)->SetPlayState(playerPlay, SL_PLAYSTATE_STOPPED)); }

		inline void Loop(bool loop) { SL((*playerSeek)->SetLoop(playerSeek, loop ? SL_BOOLEAN_TRUE : SL_BOOLEAN_FALSE, 0, SL_TIME_UNKNOWN)); }

		inline bool FinishedPlaying() {
			unsigned int playing;
			SL((*playerPlay)->GetPlayState(playerPlay, &playing));
			return playing != SL_PLAYSTATE_PLAYING;
		}
	};

}
