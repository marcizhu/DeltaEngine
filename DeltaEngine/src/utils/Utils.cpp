#include <string>

#include "utils.h"
#include "types.h"
#include "PlatformConsole.h"
#include "PlatformTime.h"

using namespace std;

namespace DeltaEngine {
	namespace Utils {

		Types::timestamp getSystemTime()
		{
			return Internal::getSystemTime();
		}

		Types::timestamp getUTCTime()
		{
			return Internal::getUTCTime();
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
			Internal::PlatformGotoxy(x, y);
		}

		void setConsoleColor(int color)
		{ 
			Internal::PlatformSetConsoleColor(color);
			
		}

	}
}