#pragma once

#include <Windows.h>
#include <stdio.h>

#include "internal.h"
#include "log.h"
#include "types.h"

using namespace DeltaEngine::Types;

namespace DeltaEngine {
	namespace Internal {

#ifdef _WIN32

		void PlatformLogMessage(uint32 level, const char* message)
		{
			switch (level)
			{
			case DELTAENGINE_LOG_LEVEL_FATAL:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xCF); break;

			case DELTAENGINE_LOG_LEVEL_ERROR:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C); break;

			case DELTAENGINE_LOG_LEVEL_WARN:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E); break;

			}

			printf("%s", message);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
		}

#else
#error("This platform is not supported")
#endif

	}
}