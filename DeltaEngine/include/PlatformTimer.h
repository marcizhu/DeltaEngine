#pragma once

#include "types.h"

using namespace DeltaEngine::Types;

namespace DeltaEngine {
	namespace Internal {

#if defined(_WIN32)
#	ifdef _WINDOWS_
#		undef _WINDOWS_
#	endif
#include <Windows.h>

		static __forceinline uint64 getTimerFrequency()
		{
			LARGE_INTEGER frequency;
			QueryPerformanceFrequency(&frequency);

			return frequency.QuadPart;
		}

		static __forceinline uint64 getCurrentCount()
		{
			LARGE_INTEGER count;
			QueryPerformanceCounter(&count);

			return count.QuadPart;
		}

#elif defined(__unix__) || defined(__GNUC__) || defined(__GNUG__)
#include <unistd.h>

		static __forceinline uint64 rdtsc()
		{
			uint32 lo, hi;

			__asm__ __volatile__("rdtsc" : "=a" (lo), "=d" (hi));

			return (uint64)hi << 32 | lo;
		}

		static __forceinline uint64 getTimerFrequency()
		{
			uint64 before, after;

			before = rdtsc();
			usleep(1000000); //10^6 microseconds = 1 second
			after = rdtsc();

			return (after - before) / 1000;
		}

		static __forceinline uint64 getCurrentCount()
		{
			return rdtsc();
		}

#else
#error This platform is not supported!
#endif

	}
}