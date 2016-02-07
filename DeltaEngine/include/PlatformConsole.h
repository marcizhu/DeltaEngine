#pragma once

namespace DeltaEngine {
	namespace Internal {

#ifdef _WIN32
#undef _WINDOWS_
#include <Windows.h>

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

#else
#error("This platform is not supported")
#endif

	}
}