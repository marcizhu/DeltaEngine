#include <gorilla\ga.h>
#include <gorilla\gau.h>

#include "soundManager.h"

namespace DeltaEngine {
	namespace Audio {

		gau_Manager* SoundManager::manager = nullptr;
		ga_Mixer* SoundManager::mixer = nullptr;

		std::vector<Sound*> SoundManager::sounds;

		void SoundManager::init()
		{
			gc_initialize(0);
			manager = gau_manager_create();
			mixer = gau_manager_mixer(manager);
		}

		void SoundManager::add(Sound* sound)
		{
			sounds.push_back(sound);
		}

		Sound* SoundManager::get(const std::string& name)
		{
			for (Sound* sound : sounds)
			{
				if (sound->getName() == name)
					return sound;
			}
			return nullptr;
		}

		void SoundManager::clean()
		{
			for (int i = 0; i < sounds.size(); i)
				delete sounds[i];

			gau_manager_destroy(manager);
			gc_shutdown();
		}

		void SoundManager::update()
		{
			gau_manager_update(manager);
		}
	}
}