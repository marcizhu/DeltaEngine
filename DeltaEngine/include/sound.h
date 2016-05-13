#pragma once

#include <string>
#include <vector>

#include <gorilla\ga.h>
#include <gorilla\gau.h>

#include "internal.h"
#include "vector3d.h"
#include "types.h"

using namespace std;

namespace DeltaEngine {
	namespace Sound {

		class Sound
		{
		private:
			string name;

			bool playing;
			bool ready;
			int playInstances;

			ga_Sound* sound;
			ga_Handle* handle;

			static void destroy_on_finish(ga_Handle* in_handle, void* in_context);
			static void loop_on_finish(ga_Handle* in_handle, void* in_context);

			static void loadSound(Sound* obj, const string& filename);
			static void playSound(Sound* obj, bool loop);
			static void setParam(Sound* obj, gc_int32 param, float value);

		public:
			DELTAENGINE_API Sound(const string& name, const string& filename);
			DELTAENGINE_API ~Sound() { ga_sound_release(sound); };

			DELTAENGINE_API void play();
			DELTAENGINE_API void pause() { playing = false; ga_handle_stop(handle); }
			DELTAENGINE_API void stop();
			DELTAENGINE_API void loop();
			DELTAENGINE_API void resume() { ga_handle_play(handle); };

			DELTAENGINE_API inline void setPan(float value);
			DELTAENGINE_API inline void setPitch(float value);
			DELTAENGINE_API inline void setGain(float gain);

			DELTAENGINE_API inline const string& getName() const { return name; }

			DELTAENGINE_API inline const bool isReady() const { return ready; };

			DELTAENGINE_API void setPosition(Maths::Vector2D position, float intensity = 1.0f) // AABB area
			{
				this->setPan((1.0f - intensity) + (intensity * position.x));
				//this->setGain(1 / 1 + position.distance());
			}
		};

	}
}