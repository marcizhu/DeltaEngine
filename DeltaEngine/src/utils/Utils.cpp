#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

#include "utils.h"
#include "types.h"
#include "PlatformUtils.h"

using namespace std;

namespace DeltaEngine {
	namespace Utils {

		Types::timestamp getSystemTime()
		{
			return Platform::getSystemTime();
		}

		Types::timestamp getUTCTime()
		{
			return Platform::getUTCTime();
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

		vector<string> splitString(const std::string& str, char delimiter)
		{
			vector<string> split;
			stringstream ss(str);
			string item;

			while (getline(ss, item, delimiter)) split.push_back(item);

			return split;
		}

		void gotoxy(int x, int y)
		{
			Platform::PlatformGotoxy(x, y);
		}

		void setConsoleColor(int color)
		{
			Platform::PlatformSetConsoleColor(color);
		}

		void clearScreen()
		{
			Platform::PlatformCls();
		}

		string precision_to_string(const float val, char n)
		{
			std::ostringstream out;
			out << std::setprecision(n) << val;
			return out.str();
		}

		Types::timestamp getBuildTime()
		{
			return Platform::PlatformGetBuildTime();
		}

		void printBuildTime()
		{
			Platform::PlatformSetConsoleColor(0x03);

			printf("Build time: ");
			printTimestamp(getBuildTime());

			Platform::PlatformSetConsoleColor(0x07);
		}

		void printDate(const Types::date& date)
		{
			printf("%02i/%02i/%02i", date.Day, date.Month, date.Year);
		}

		void printTime(const Types::time& time)
		{
			printf("%02i:%02i:%02i", time.Hour, time.Minute, time.Second);
		}

		void printTimestamp(const Types::timestamp& t)
		{
			printf("%02i/%02i/%02i  %02i:%02i:%02i", t.Day, t.Month, t.Year, t.Hour, t.Minute, t.Second);
		}

	}
}