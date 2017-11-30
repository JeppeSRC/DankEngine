#pragma once

#include <vector>

#include "audio.h"

namespace dank {

	class AudioPlaylist {
	private:
	//	std::vector<Audio*> sounds;
		List<Audio*> sounds;
		
		unsigned int currentSound = 0;

		bool playing = false;
		bool autodelete = false;
	public:
		AudioPlaylist(bool autodelete) : autodelete(autodelete) { }
		~AudioPlaylist() {
			if (autodelete)
				for (size_t i = 0; i < sounds.GetSize(); i++)
					delete sounds[i];
		}


		void Update() {
			if (sounds[currentSound]->FinishedPlaying() && playing) {
				if (++currentSound > sounds.GetSize() - 1)
					currentSound = 0;
				sounds[currentSound]->Play();
			}
			
		}

		inline void Stop() {
			playing = false;
			sounds[currentSound]->Stop();
			currentSound = 0;
		}

		inline void Pause() {
			playing = false;
			sounds[currentSound]->Pause();
		}

		inline void Play() {
			if (!playing) {
				playing = true;
				sounds[currentSound]->Play();
			}
		}

		inline void Next() {
			Stop();
			if (++currentSound > sounds.GetSize() - 1)
				currentSound = 0;
			sounds[currentSound]->Play();
		}

		inline void Previous() {
			Stop();
			if (--currentSound < 0)
				currentSound = sounds.GetSize() - 1;
			sounds[currentSound]->Play();
		}

		inline void Push(Audio* audio) {
			sounds.Push_back(audio);
		}
	};

}
