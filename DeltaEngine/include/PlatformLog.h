#pragma once

#include <stdio.h>

#include "internal.h"
#include "log.h"

#define DELTAENGINE_LOG_LEVEL_FATAL 0
#define DELTAENGINE_LOG_LEVEL_ERROR 1
#define DELTAENGINE_LOG_LEVEL_WARN  2
#define DELTAENGINE_LOG_LEVEL_INFO  3

namespace DeltaEngine {
	namespace Internal {

#ifdef _WIN32
#include <Windows.h>

		void PlatformLogMessage(unsigned int level, const char* message)
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