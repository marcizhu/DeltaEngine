#pragma once

#include <stdio.h>
#include <ctime>

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
#	include <Windows.h>

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
			x >= 0 ? dwPos.X = x : dwPos.X = SBInfo.dwCursorPosition.X;
			y >= 0 ? dwPos.Y = y : dwPos.Y = SBInfo.dwCursorPosition.Y;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), dwPos);
		}

		static __forceinline void PlatformCls()
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			COORD coordScreen = { 0, 0 };
			DWORD cCharsWritten;
			CONSOLE_SCREEN_BUFFER_INFO csbi;

			if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;

			DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

			if (!FillConsoleOutputCharacter(hConsole, (TCHAR) ' ', dwConSize, coordScreen, &cCharsWritten)) return;
			if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;
			if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten)) return;

			PlatformGotoxy(0, 0);
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

			case DELTAENGINE_LOG_LEVEL_DEBUG:
				PlatformSetConsoleColor(0x03); break;
			}

			printf("%s", message);
			PlatformSetConsoleColor(0x0F);
		}

		static Types::timestamp toTimestamp(const struct tm* time)
		{
			Types::timestamp ttamp;

			ttamp.Year = time->tm_year + 1900;
			ttamp.Month = time->tm_mon + 1;
			ttamp.Day = time->tm_mday;
			ttamp.Hour = time->tm_hour;
			ttamp.Minute = time->tm_min;
			ttamp.Second = time->tm_sec;
			ttamp.DayOfWeek = time->tm_wday;

			return ttamp;
		}

		extern "C" IMAGE_DOS_HEADER __ImageBase;

		static __forceinline Types::timestamp PlatformGetBuildTime()
		{
			const IMAGE_NT_HEADERS *nt_header = (const IMAGE_NT_HEADERS *)((char *)&__ImageBase + __ImageBase.e_lfanew);

			struct tm* now = std::localtime((const time_t*)&(nt_header->FileHeader.TimeDateStamp));

			Types::timestamp time = toTimestamp(now);

			return time;
		}

		static __forceinline void PlatformSleep(unsigned int milliseconds)
		{
			Sleep(milliseconds);
		}

#elif defined(DELTAENGINE_PLATFORM_LINUX)
#	include <unistd.h> // for usleep

		static __attribute__((always_inline)) Types::timestamp getSystemTime()
		{
			std::time_t t = std::time(nullptr);

			Types::timestamp time = toTimestamp(std::localtime((const time_t*)&t));

			return time;
		}

		static __attribute__((always_inline)) Types::timestamp getUTCTime()
		{
			std::time_t t = std::time(nullptr);

			Types::timestamp time = toTimestamp(std::gmtime((const time_t*)&t));

			return time;
		}

		static __attribute__((always_inline)) void PlatformSetConsoleColor(int color)
		{
			// TODO: Add linux code to change the color of the text on the console
		}

		static __attribute__((always_inline)) void PlatformGotoxy(int x, int y)
		{
			if (x < 0 && y < 0) DELTAENGINE_ERROR("PlatformGotoxy: Not implemented yet!");

			printf("\x1b[%d;%df", y, x);
		}

		static __attribute__((always_inline)) void PlatformCls()
		{
			printf("\033[2J"); // cls
			printf("\x1b[%d;%df", 0, 0); // gotoxy
		}

		// NOTE: PlatformLogMessage is platform-independent?

		static __attribute__((always_inline)) Types::timestamp PlatformGetBuildTime()
		{
			// TODO: Add linux code to read the build time
		}

		static __attribute__((always_inline)) void PlatformSleep(unsigned int milliseconds)
		{
			usleep(milliseconds * 1000);
		}

#else
#	error This platform is not supported!
#endif

	}
}