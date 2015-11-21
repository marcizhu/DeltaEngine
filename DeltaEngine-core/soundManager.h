#pragma once

#ifndef __DELTAENGINE_SOUND_MANAGER__
#define __DELTAENGINE_SOUND_MANAGER__

#define GAU_THREAD_POLICY_MULTI 2

#include <gorilla\ga.h>
#include <gorilla\gau.h>
#include <vector>

#include "DeltaEngine.h"
#include "sound.h"

namespace DeltaEngine {
	namespace Audio {

		class SoundManager
		{
		private:

			friend class Sound;

			static gau_Manager* manager;
			static ga_Mixer* mixer;

			static std::vector<Sound*> sounds;

		public:
			DELTAENGINE_API static void init();
			DELTAENGINE_API static void add(Sound* sound);
			DELTAENGINE_API static Sound* get(const std::string& name);
			DELTAENGINE_API static void update();
			DELTAENGINE_API static void clean();

			//SoundManager() {}
		};


	}
}

#endif