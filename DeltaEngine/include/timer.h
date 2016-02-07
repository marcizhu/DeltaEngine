#pragma once

#include <time.h>

#include "internal.h"
#include "types.h"

using namespace DeltaEngine::Types;

namespace DeltaEngine {
	namespace Utils {

		class Timer {
		private:
			clock_t begin;

		public:
			Timer() { restart(); };

			inline void restart() { begin = (uint64)clock(); };

			inline float getElapsedTime() const { return ((float)clock() - begin) / CLOCKS_PER_SEC; };
			inline bool isOver(float secs) { if (secs >= getElapsedTime()) { restart(); return true; } return false; };
		};

	}
}