#include <string>
#include <sstream>
#include <vector>

#include <gorilla\ga.h>
#include <gorilla\gau.h>

#include "sound.h"
#include "soundManager.h"

using namespace std;

namespace DeltaEngine {
	namespace Audio {

		Sound::Sound(const std::string& name, const std::string& filename)
			: name(name), filename(filename), playing(false)
		{

			std::vector<std::string> split;
			std::stringstream ss(filename);
			std::string item;
			while (std::getline(ss, item, '.')) split.push_back(item);

			if (split.size() < 2)
			{
				std::cout << "[Sound] Invalid file name '" << filename << "'!" << std::endl;
				return;
			}
			sound = gau_load_sound_file(filename.c_str(), split.back().c_str());
			
			if (sound == nullptr) std::cout << "[Sound] Could not load file '" << filename << "'!" << std::endl;
		}
		
		Sound::~Sound()
		{
			ga_sound_release(sound);
		}
		
		void Sound::play()
		{
			gc_int32 quit = 0;
			handle = gau_create_handle_sound(SoundManager::mixer, sound, &destroy_on_finish, &quit, NULL);
			handle->sound = this;
			ga_handle_play(handle);
			playing = true;
		}
		
		void Sound::loop()
		{
			gc_int32 quit = 0;
			handle = gau_create_handle_sound(SoundManager::mixer, sound, &loop_on_finish, &quit, NULL);
			handle->sound = this;
			ga_handle_play(handle);
			playing = true;
		}
		
		void Sound::resume()
		{
			ga_handle_play(handle);
		}
		
		void Sound::pause()
		{
			playing = false;
			ga_handle_stop(handle);
		}
		
		void Sound::stop()
		{
			if (!playing) return;
			
			ga_handle_stop(handle);
			playing = false;
		}
		
		void Sound::destroy_on_finish(ga_Handle* in_handle, void* in_context)
		{
			Sound* sound = (Sound*)in_handle->sound;
			sound->stop();
		}
		
		void Sound::loop_on_finish(ga_Handle* in_handle, void* in_context)
		{
			Sound* sound = (Sound*)in_handle->sound;
			sound->loop();
			ga_handle_destroy(in_handle);
		}

	}
}