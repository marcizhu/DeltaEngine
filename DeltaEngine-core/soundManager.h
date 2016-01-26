#pragma once

#include <gorilla\ga.h>
#include <gorilla\gau.h>

#include <vector>

#include "DeltaEngine.h"
#include "sound.h"

namespace DeltaEngine {
	namespace Sound {

		class SoundManager
		{
		private:

			friend class Sound;

			static gau_Manager* manager;
			static ga_Mixer* mixer;

			static std::vector<Sound*> sounds;

		public:
			DELTAENGINE_API ~SoundManager() { clean(); };
			DELTAENGINE_API static void init();
			DELTAENGINE_API static void add(Sound* sound) { sounds.push_back(sound); };
			DELTAENGINE_API static Sound* get(const std::string& name);
			DELTAENGINE_API inline static void update() { gau_manager_update(manager); }
			DELTAENGINE_API static void clean();
			DELTAENGINE_API static bool areAllSoundsLoaded();
		};


	}
}