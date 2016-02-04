#pragma once

#include <Windows.h>

namespace DeltaEngine {
	namespace Internal {

#ifdef _WIN32

		void PlatformSetConsoleColor(int color) 
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		}

		inline void PlatformGotoxy(int x, int y)
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