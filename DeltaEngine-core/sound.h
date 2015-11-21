#pragma once

#ifndef __DELTAENGINE_SOUND__
#define __DELTAENGINE_SOUND__

#include <string>

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
			bool looping = true;

			gau_Manager* manager;
			ga_Mixer* mixer;
			ga_Sound* sound;
			ga_Handle* handle;

			static void destroy_on_finish(ga_Handle* in_handle, void* in_context);
			static void loop_on_finish(ga_Handle* in_handle, void* in_context);
			
		public:
			DELTAENGINE_API Sound(const string& name, const string& filename);
			DELTAENGINE_API ~Sound();

			DELTAENGINE_API void play();
			DELTAENGINE_API void pause();
			DELTAENGINE_API void stop();
			DELTAENGINE_API void loop();
			DELTAENGINE_API void resume();

			DELTAENGINE_API void setPitch(float value) { ga_handle_setParamf(handle, GA_HANDLE_PARAM_PITCH, value); };
			DELTAENGINE_API void setGain(float gain) { ga_handle_setParamf(handle, GA_HANDLE_PARAM_GAIN, gain); };
			DELTAENGINE_API void setPan(float value) { ga_handle_setParamf(handle, GA_HANDLE_PARAM_PAN, value); };

			DELTAENGINE_API inline const std::string& getName() const { return name; }
			DELTAENGINE_API inline const std::string& getFileName() const { return filename; }

			//TODO: Implement set3DPosition() !
			DELTAENGINE_API void set3DPosition(Maths::Vector3D position);

		};

	}
}

#endif