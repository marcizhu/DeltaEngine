#include <thread>

#include "Playlist.h"
#include "log.h"
#include "platformUtils.h"

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

		void Playlist::playSounds(Playlist* playlist)
		{
			for (unsigned int i = 0; i < playlist->list.size(); i++)
			{
				//DELTAENGINE_INFO("[Playlist] Currently playing \"", playlist->list[i]->getName(), "\"");

				playlist->list[i]->play();

				do { Platform::PlatformSleep(1); } while(playlist->list[i]->isPlaying());
			}

			//DELTAENGINE_INFO("[Playlist] Playlist ended!");

			// TODO: Add callback / event
		}

		void Playlist::play()
		{
			std::thread playlist(playSounds, this);
			playlist.detach();
		}

	}
}