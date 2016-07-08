#pragma once

#include <vector>
#include <string>

#include "internal.h"
#include "sound.h"

namespace DeltaEngine {
	namespace Sound {

		class Playlist
		{
		private:
			unsigned int current;
			std::vector<Sound*> list;

			static void playSounds(Playlist* list);

		public:
			DELTAENGINE_API Playlist() : current(0) { }

			DELTAENGINE_API void add(Sound* sound) { list.push_back(sound); }
			DELTAENGINE_API void remove(std::string name);

			DELTAENGINE_API void play();

			DELTAENGINE_API void clean() { list.clear(); };
		};

	}
}