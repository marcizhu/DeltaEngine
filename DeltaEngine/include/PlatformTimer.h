#pragma once

#include "internal.h"
#include "types.h"

using namespace DeltaEngine::Types;

namespace DeltaEngine {
	namespace Platform {

#if defined(DELTAENGINE_PLATFORM_WINDOWS)
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

#elif defined(DELTAENGINE_PLATFORM_LINUX)
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