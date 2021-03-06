#pragma once

//#include <time.h>

#include "internal.h"
#include "types.h"

#include "PlatformTimer.h"

using namespace DeltaEngine::Types;

namespace DeltaEngine {
	namespace Utils {

		class Timer {
		private:
			uint64 begin;
			uint64 freq;

		public:
			Timer() { freq = Platform::getTimerFrequency(); restart(); };

			inline void restart() { begin = Platform::getCurrentCount(); };

			inline float getElapsedTime() const { return (float)(Platform::getCurrentCount() - begin) / freq; };
			inline bool isOver(float secs) { if (secs >= getElapsedTime()) { restart(); return true; } return false; };
		};

	}
}