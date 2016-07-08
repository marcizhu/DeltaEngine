#include <thread>
#include <Windows.h>

#include "Playlist.h"
#include "log.h"

namespace DeltaEngine {
	namespace Sound {

		void Playlist::remove(std::string name)
		{
			for (unsigned int i = 0; i < list.size(); i++)
			{
				if (list[i]->getName() == name)
				{
					list.erase(list.begin() + i);
					break;
				}
			}
		}

		void Playlist::playSounds(Playlist* list)
		{
			for (Sound* sound : list->list)
			{
				DELTAENGINE_INFO("[Playlist] Currently playing \"", list->list[list->current++]->getName(), "\"");

				sound->play();

				do { Sleep(1); } while(sound->isPlaying());
			}

			DELTAENGINE_INFO("[Playlist] Playlist ended!");

			// TODO: Add callback / event
		}

		void Playlist::play()
		{
			std::thread playlist(playSounds, this);
			playlist.detach();
		}

	}
}