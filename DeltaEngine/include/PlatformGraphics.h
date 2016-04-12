#pragma once

namespace DeltaEngine {
	namespace Platform {

#if defined(DELTAENGINE_PLATFORM_WINDOWS)
#include <GLEW\glew.h>
#include <GLEW\wglew.h>

		static void PlatformSwapInterval(unsigned int interval)
		{
			wglSwapIntervalEXT(interval);
		}
#else
#	error This platform is not supported!
#endif

	}
}