#include <gorilla\ga.h>
#include <gorilla\gau.h>

#include <vector>

#include "soundManager.h"
#include "types.h"

using namespace DeltaEngine::Types;

namespace DeltaEngine {
	namespace Sound {

		gau_Manager* SoundManager::manager = nullptr;
		ga_Mixer* SoundManager::mixer = nullptr;

		std::vector<Sound*> SoundManager::sounds;

		void SoundManager::init()
		{
			gc_initialize(0);
			manager = gau_manager_create();
			mixer = gau_manager_mixer(manager);
		}

		Sound* SoundManager::get(const std::string& name)
		{
			for (Sound* sound : sounds)
				if (sound->getName() == name) return sound;

			return nullptr;
		}

		void SoundManager::clean()
		{
			for (uint32 i = 0; i < sounds.size(); i++)
				delete sounds[i];

			gau_manager_destroy(manager);
			gc_shutdown();
		}

		bool SoundManager::areAllSoundsLoaded()
		{
			for (uint32 i = 0; i < sounds.size(); i++)
				if (sounds[i]->isReady() == false) return false;

			return true;
		}

	}
}