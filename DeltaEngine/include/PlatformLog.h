#pragma once

#include <stdio.h>

#include "internal.h"
#include "log.h"
#include "LogLevels.h"
#include "PlatformConsole.h"

namespace DeltaEngine {
	namespace Internal {

#ifdef _WIN32

		void PlatformLogMessage(unsigned int level, const char* message)
		{
			switch (level)
			{
			case DELTAENGINE_LOG_LEVEL_FATAL:
				PlatformSetConsoleColor(0xCF); break;

			case DELTAENGINE_LOG_LEVEL_ERROR:
				PlatformSetConsoleColor(0x0C); break;

			case DELTAENGINE_LOG_LEVEL_WARN:
				PlatformSetConsoleColor(0x0E); break;
			}

			printf("%s", message);
			PlatformSetConsoleColor(0x0F);
		}

#else
#error("This platform is not supported")
#endif

	}
}