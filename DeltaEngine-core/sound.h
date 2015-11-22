#pragma once

#ifndef __DELTAENGINE_SOUND__
#define __DELTAENGINE_SOUND__

#include <string>
#include <vector>

#include <gorilla\ga.h>
#include <gorilla\gau.h>

#include "DeltaEngine.h"
#include "vector3d.h"

using namespace std;

namespace DeltaEngine {
	namespace Audio {

		class Sound {
		private:
			string name;
			string filename;

			bool playing = false;
			//bool looping = true;
			bool ready = false;

			ga_Sound* sound;
			ga_Handle* handle;

			static void destroy_on_finish(ga_Handle* in_handle, void* in_context);
			static void loop_on_finish(ga_Handle* in_handle, void* in_context);

			static void loadSound(Sound* obj, vector<string> split);
			static void Sound::playSound(Sound* obj, bool loop);
			
		public:
			DELTAENGINE_API Sound(const string& name, const string& filename);
			DELTAENGINE_API ~Sound() { ga_sound_release(sound); };

			DELTAENGINE_API void play();
			DELTAENGINE_API void pause() { playing = false; ga_handle_stop(handle); }
			DELTAENGINE_API void stop();
			DELTAENGINE_API void loop();
			DELTAENGINE_API void resume() { ga_handle_play(handle); };

			DELTAENGINE_API inline void setPitch(float value) { ga_handle_setParamf(handle, GA_HANDLE_PARAM_PITCH, value); };
			DELTAENGINE_API inline void setGain(float gain) { ga_handle_setParamf(handle, GA_HANDLE_PARAM_GAIN, gain); };
			DELTAENGINE_API inline void setPan(float value) { ga_handle_setParamf(handle, GA_HANDLE_PARAM_PAN, value); };

			DELTAENGINE_API inline const string& getName() const { return name; }
			DELTAENGINE_API inline const string& getFileName() const { return filename; }

			DELTAENGINE_API inline const bool isReady() { return ready; };

			//TODO: Implement set3DPosition() !
			DELTAENGINE_API void set3DPosition(Maths::Vector3D position);

		};

	}
}

#endif