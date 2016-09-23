#pragma once

namespace DeltaEngine {
	namespace Platform {

#if defined(DELTAENGINE_PLATFORM_WINDOWS)
#include <GLEW\glew.h>
#include <GLEW\wglew.h>

		static __forceinline void PlatformSwapInterval(int interval) // TODO: -1 = adaptive sync? Test!
		{
			wglSwapIntervalEXT(interval);
		}

#elif defined(DELTAENGINE_PLATFORM_LINUX)

		static __attribute__((always_inline)) void PlatformSwapInterval(int interval)
		{
			//GLX_EXT_swap_control(, , interval)
		}

#else
#	error This platform is not supported!
#endif

	}
}