#pragma once

#include <vector>

#include "audio.h"

namespace dank {

	class AudioPlaylist {
	private:
		std::vector<Audio*> sounds;
		
		unsigned int currentSound = 0;

		bool playing = false;
		bool autodelete = false;
	public:
		AudioPlaylist(bool autodelete): autodelete(autodelete) { }
		~AudioPlaylist() {
			if (autodelete)
				for (size_t i = 0; i < sounds.size(); i++)
					delete sounds[i];
		}


		void Update() {
			if (sounds[currentSound]->FinishedPlaying() && playing) {
				if (++currentSound > sounds.size() - 1)
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
			if (++currentSound > sounds.size() - 1)
				currentSound = 0;
			sounds[currentSound]->Play();
		}

		inline void Previous() {
			Stop();
			if (--currentSound < 0)
				currentSound = sounds.size() - 1;
			sounds[currentSound]->Play();
		}

		inline void Push(Audio* audio) {
			sounds.push_back(audio);
		}
	};

}
