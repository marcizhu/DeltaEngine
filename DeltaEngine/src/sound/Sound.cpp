#include <string>
#include <thread>
#include <Windows.h>

#include <gorilla\ga.h>
#include <gorilla\gau.h>

#include "sound.h"
#include "soundManager.h"
#include "utils.h"
#include "log.h"

using namespace std;

namespace DeltaEngine {
	namespace Sound {

		// TODO: Load stream sounds
		void Sound::loadSound(Sound* obj, const string& filename)
		{
			vector<string> split = Utils::splitString(filename, '.');

			if (split.size() < 2)
			{
				DELTAENGINE_ERROR("[Sound] Invalid file name '", filename, "'!");
				return;
			}

			obj->sound = gau_load_sound_file(filename.c_str(), split.back().c_str());

			if (obj->sound == nullptr) DELTAENGINE_ERROR("[Sound] Could not load file '", filename, "'!");

			obj->ready = true;
		}

		Sound::Sound(const string& name, const string& filename)
			: name(name), playing(false), ready(false), playInstances(0)
		{
			thread audioThread(loadSound, this, filename);
			audioThread.detach();
		}

		void Sound::playSound(Sound* obj, bool loop)
		{
			while (!obj->ready); // do nothing, just wait

			obj->handle = gau_create_handle_sound(SoundManager::mixer, obj->sound, loop ? &loop_on_finish : &destroy_on_finish, NULL, NULL);
			obj->handle->sound = obj;
			obj->playing = true;
			obj->playInstances++;

			ga_handle_play(obj->handle);
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
			if (!playing || playInstances > 0) return;

			ga_handle_stop(handle);
			ga_handle_destroy(handle);
			playing = false;
			playInstances = 0;
		}

		void Sound::setParam(Sound* obj, gc_int32 param, float value)
		{
			while (!obj->ready);

			Sleep(1);

			ga_handle_setParamf(obj->handle, param, value);
		}

		void Sound::setPan(float value)
		{
			thread audioThread(setParam, this, GA_HANDLE_PARAM_PAN, value);
			audioThread.detach();
		}

		void Sound::setPitch(float value)
		{
			thread audioThread(setParam, this, GA_HANDLE_PARAM_PITCH, value);
			audioThread.detach();
		}

		void Sound::setGain(float gain)
		{
			thread audioThread(setParam, this, GA_HANDLE_PARAM_GAIN, gain);
			audioThread.detach();
		}

		void Sound::destroy_on_finish(ga_Handle* in_handle, void* in_context)
		{
			Sound* sound = (Sound*)in_handle->sound;
			sound->playInstances--;
			sound->stop();
		}

		void Sound::loop_on_finish(ga_Handle* in_handle, void* in_context)
		{
			Sound* sound = (Sound*)in_handle->sound;
			sound->playInstances--;
			sound->loop();
		}

	}
}