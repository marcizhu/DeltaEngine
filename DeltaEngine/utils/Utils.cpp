#include <string>
#include <Windows.h>

#include "utils.h"
#include "types.h"

using namespace std;

namespace DeltaEngine {
	namespace Utils {

		Types::timestamp getSystemTime()
		{
			SYSTEMTIME st;
			GetLocalTime(&st);

			Types::timestamp ret;
			memcpy_s(&ret, sizeof(ret), &st, sizeof(ret));
			return ret;
		}

		Types::timestamp getUTCTime()
		{
			SYSTEMTIME st;
			GetSystemTime(&st);

			Types::timestamp ret;
			memcpy_s(&ret, sizeof(ret), &st, sizeof(ret));
			return ret;
		}

		Types::time timestampToTime(const Types::timestamp& t)
		{
			Types::time ret;
			memcpy_s(&ret, sizeof(ret), &t.Hour, sizeof(ret));
			return ret;
		}

		Types::date timestampToDate(const Types::timestamp& t)
		{
			Types::date ret;
			memcpy_s(&ret, sizeof(ret), &t.Year, sizeof(ret));
			return ret;
		}

		string getCurrentPath()
		{
			char path[1024];
			memset(path, 0, 1024);
			if (!GetCurrentDir(path, sizeof(path))) return string("NULL");
			
			return path;
		}

		void gotoxy(int x, int y)
		{
			CONSOLE_SCREEN_BUFFER_INFO SBInfo;
			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &SBInfo);

			COORD dwPos;
			x > 0 ? dwPos.X = x : dwPos.X = SBInfo.dwCursorPosition.X;
			y > 0 ? dwPos.Y = y : dwPos.Y = SBInfo.dwCursorPosition.Y;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), dwPos);
		}
		void setConsoleColor(int color)
		{ 
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); 
		};

	}
}