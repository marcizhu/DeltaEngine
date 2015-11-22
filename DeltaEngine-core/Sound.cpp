#include <string>
#include <sstream>
#include <vector>
#include <thread>

#include <gorilla\ga.h>
#include <gorilla\gau.h>

#include "sound.h"
#include "soundManager.h"

using namespace std;

namespace DeltaEngine {
	namespace Audio {

		void Sound::loadSound(Sound* obj, vector<string> split)
		{
			obj->sound = gau_load_sound_file(obj->filename.c_str(), split.back().c_str());

			if (obj->sound == nullptr)
			{
#ifdef DELTAENGINE_DEBUG
				cout << "[Sound] Could not load file '" << obj->filename << "'!" << endl;
#endif
			}

			obj->ready = true;
		}

		Sound::Sound(const string& name, const string& filename)
			: name(name), filename(filename), playing(false), ready(false)
		{

			vector<string> split;
			stringstream ss(filename);
			string item;
			while (getline(ss, item, '.')) split.push_back(item);

			if (split.size() < 2)
			{
#ifdef DELTAENGINE_DEBUG
				std::cout << "[Sound] Invalid file name '" << filename << "'!" << std::endl;
#endif
				return;
			}

			thread audioThread(loadSound, this, split);
			audioThread.detach();
		}
		
		void Sound::playSound(Sound* obj, bool loop)
		{
			while (!obj->ready); // do nothing, just wait

			obj->handle = gau_create_handle_sound(SoundManager::mixer, obj->sound, loop ? &loop_on_finish : &destroy_on_finish, NULL, NULL);
			obj->handle->sound = obj;
			ga_handle_play(obj->handle);
			obj->playing = true;
		}

		void Sound::play()
		{
			thread audioThread(playSound, this, false);
			audioThread.detach();
		}
		
		void Sound::loop()
		{
			thread audioThread(playSound, this, true);
			audioThread.detach();
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
		}

	}
}