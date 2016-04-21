#pragma once

#include <stdio.h>

#include "types.h"
#include "internal.h"
#include "log.h"
#include "LogLevels.h"

namespace DeltaEngine {
	namespace Platform {

#if defined(DELTAENGINE_PLATFORM_WINDOWS)
#	ifdef _WINDOWS_
#		undef _WINDOWS_
#	endif
#include <Windows.h>

		static __forceinline Types::timestamp getSystemTime()
		{
			SYSTEMTIME st;
			GetLocalTime(&st);

			Types::timestamp ret;
			memcpy_s(&ret, sizeof(ret), &st, sizeof(ret));
			return ret;
		}

		static __forceinline Types::timestamp getUTCTime()
		{
			SYSTEMTIME st;
			GetSystemTime(&st);

			Types::timestamp ret;
			memcpy_s(&ret, sizeof(ret), &st, sizeof(ret));
			return ret;
		}

		static __forceinline void PlatformSetConsoleColor(int color)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		}

		static __forceinline void PlatformGotoxy(int x, int y)
		{
			CONSOLE_SCREEN_BUFFER_INFO SBInfo;
			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &SBInfo);

			COORD dwPos;
			x > 0 ? dwPos.X = x : dwPos.X = SBInfo.dwCursorPosition.X;
			y > 0 ? dwPos.Y = y : dwPos.Y = SBInfo.dwCursorPosition.Y;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), dwPos);
		}

		static __forceinline void PlatformLogMessage(unsigned int level, const char* message)
		{
			switch (level)
			{
			case DELTAENGINE_LOG_LEVEL_FATAL:
				PlatformSetConsoleColor(0xCF); break;

			case DELTAENGINE_LOG_LEVEL_ERROR:
				PlatformSetConsoleColor(0x0C); break;

			case DELTAENGINE_LOG_LEVEL_WARN:
				PlatformSetConsoleColor(0x0E); break;

			case DELTAENGINE_LOG_LEVEL_INFO:
				PlatformSetConsoleColor(0x0F); break;

			case DELTAENGINE_LOG_LEVEL_MSG:
				PlatformSetConsoleColor(0x03); break;
			}

			printf("%s", message);
			PlatformSetConsoleColor(0x0F);
		}

#else
#error This platform is not supported!
#endif

	}
}