#pragma once

#include <time.h>

#include "DeltaEngine.h"
#include "types.h"

//using namespace DeltaEngine::Types;

namespace DeltaEngine {
	namespace Utils {

		class Timer {
		private:
			Types::uint64 begin;

		public:
			Timer() { restart(); };

			inline void restart() { begin = (Types::uint64)clock(); };

			inline Types::uint64 getElapsedTime() const { return ((Types::uint64)clock() - begin) / CLOCKS_PER_SEC; };
			inline bool isOver(Types::uint64 seconds) const { return seconds >= getElapsedTime(); };
		};

	}
}