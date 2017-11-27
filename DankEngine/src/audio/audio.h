#pragma once

#include "utils/string.h"
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

		inline void Play() { (*playerPlay)->SetPlayState(playerPlay, SL_PLAYSTATE_PLAYING); }
		inline void Pause() { (*playerPlay)->SetPlayState(playerPlay, SL_PLAYSTATE_PAUSED); }
		inline void Stop() { (*playerPlay)->SetPlayState(playerPlay, SL_PLAYSTATE_STOPPED); }

		inline void Loop(bool loop) { (*playerSeek)->SetLoop(playerSeek, loop ? SL_BOOLEAN_TRUE : SL_BOOLEAN_FALSE, 0, SL_TIME_UNKNOWN); }

		inline bool FinishedPlaying() {
			unsigned int playing;
			(*playerPlay)->GetPlayState(playerPlay, &playing);
			return playing != SL_PLAYSTATE_PLAYING;
		}
	};

}
