#include "memoryInfo.h"
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

	}
}