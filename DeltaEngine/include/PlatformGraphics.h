#pragma once

namespace DeltaEngine {
	namespace Internal {

#if defined(_WIN32)
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