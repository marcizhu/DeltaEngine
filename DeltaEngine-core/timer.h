#pragma once

#ifndef __DELTAENGINE_TIMER__
#define __DELTAENGINE_TIMER__

#include <time.h>

#include "DeltaEngine.h"
#include "types.h"

using namespace DeltaEngine::Types;

namespace DeltaEngine {
	namespace Timer {

		class Timer {
		private:
			uint64 begin;

		public:
			Timer() { reset(); };

			inline void reset() { begin = (uint64)clock(); };

			inline uint64 getElapsedTime() const { return ((uint64)clock() - begin) / CLOCKS_PER_SEC; };
			inline bool isOver(uint64 seconds) const { return seconds >= getElapsedTime(); };
		};
	}
}

#endif