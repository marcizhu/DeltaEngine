#pragma once

#include "internal.h"

namespace DeltaEngine {
	namespace Internal {

		class MemoryInfo
		{
		private:
			static unsigned int allocatedMemory;
			static unsigned int freedMemory;
			static unsigned int currentMemory;

		public:
			DELTAENGINE_API static void start();
			DELTAENGINE_API static void end();

			DELTAENGINE_API static unsigned int getAllocatedMemory();
			DELTAENGINE_API static unsigned int getFreedMemory();
			DELTAENGINE_API static unsigned int getCurrentMemory();

			DELTAENGINE_API static void allocate(unsigned int amount);
			DELTAENGINE_API static void deallocate(unsigned int amount);
		};

	}
}