#pragma once

#include <time.h>

#include "internal.h"
#include "types.h"

using namespace DeltaEngine::Types;

namespace DeltaEngine {
	namespace Utils {

		class Timer {
		private:
			uint64 begin;

		public:
			Timer() { restart(); };

			inline void restart() { begin = (uint64)clock(); };

			inline uint64 getElapsedTime() const { return ((uint64)clock() - begin) / CLOCKS_PER_SEC; };
			inline bool isOver(uint64 seconds) const { return seconds >= getElapsedTime(); };
		};

	}
}