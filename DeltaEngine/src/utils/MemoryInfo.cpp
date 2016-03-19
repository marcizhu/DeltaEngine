#include "memoryInfo.h"
#include "utils.h"
#include "log.h"

namespace DeltaEngine {
	namespace Internal {

		unsigned int MemoryInfo::allocatedMemory;
		unsigned int MemoryInfo::freedMemory;
		unsigned int MemoryInfo::currentMemory;

		void MemoryInfo::end()
		{
			DELTAENGINE_ASSERT(currentMemory == 0, "Memory leak on destruction!");
		}

		void MemoryInfo::start()
		{
			allocatedMemory = 0;
			freedMemory = 0;
			currentMemory = 0;
		}

		unsigned int MemoryInfo::getAllocatedMemory() 
		{ 
			return allocatedMemory; 
		}
		
		unsigned int MemoryInfo::getFreedMemory()
		{ 
			return freedMemory; 
		}

		unsigned int MemoryInfo::getCurrentMemory()
		{
			return currentMemory; 
		}

		void MemoryInfo::allocate(unsigned int amount)
		{
			allocatedMemory += amount;
			//currentMemory = allocatedMemory - freedMemory;
			currentMemory += amount;
		}

		void MemoryInfo::deallocate(unsigned int amount)
		{
			freedMemory += amount;
			//currentMemory = allocatedMemory - freedMemory;
			currentMemory -= amount;
		}

		std::string MemoryInfo::getAllocatedMemoryString()
		{
			unsigned int bytes = getAllocatedMemory();
			std::string ret = "Allocated memory: ";

			if (bytes >= 1024 * 1024 * 1024)
			{
				float gb = (float)bytes / (1024.0f * 1024.0f * 1024.0f);
				ret += Utils::precision_to_string(gb, 3) + " Gb";
			}
			else if (bytes >= 1024 * 1024)
			{
				float mb = (float)bytes / (1024.0f * 1024.0f);
				ret += Utils::precision_to_string(mb, 3) + " Mb";
			}
			else if (bytes >= 1024)
			{
				float kb = (float)bytes / 1024.0f;
				ret += Utils::precision_to_string(kb, 3) + " Kb";
			}
			else
			{
				ret += std::to_string(bytes) + " b";
			}

			return ret;
		}

		std::string MemoryInfo::getFreedMemoryString()
		{
			unsigned int bytes = getFreedMemory();
			std::string ret = "Freed memory: ";

			if (bytes >= 1024 * 1024 * 1024)
			{
				float gb = (float)bytes / (1024.0f * 1024.0f * 1024.0f);
				ret += Utils::precision_to_string(gb, 3) + " Gb";
			}
			else if (bytes >= 1024 * 1024)
			{
				float mb = (float)bytes / (1024.0f * 1024.0f);
				ret += Utils::precision_to_string(mb, 3) + " Mb";
			}
			else if (bytes >= 1024)
			{
				float kb = (float)bytes / 1024.0f;
				ret += Utils::precision_to_string(kb, 3) + " Kb";
			}
			else
			{
				ret += std::to_string(bytes) + " b";
			}

			return ret;
		}

		std::string MemoryInfo::getCurrentMemoryString()
		{
			unsigned int bytes = getCurrentMemory();
			std::string ret = "Current memory: ";

			if (bytes >= 1024 * 1024 * 1024)
			{
				float gb = (float)bytes / (1024.0f * 1024.0f * 1024.0f);
				ret += Utils::precision_to_string(gb, 3) + " Gb";
				DELTAENGINE_ERROR("USING OVER 1 Gb OF MEMORY!");
			}
			else if (bytes >= 1024 * 1024)
			{
				float mb = (float)bytes / (1024.0f * 1024.0f);
				ret += Utils::precision_to_string(mb, 3) + " Mb";
			}
			else if (bytes >= 1024)
			{
				float kb = (float)bytes / 1024.0f;
				ret += Utils::precision_to_string(kb, 3) + " Kb";
			}
			else
			{
				ret += std::to_string(bytes) + " b";
			}

			return ret;
		}

	}
}