#pragma once

#include <string>
#include <vector>

#include "internal.h"
#include "types.h"

#if defined(WIN32) || defined(_WIN32)
	#include <direct.h>
	#define GetCurrentDir _getcwd
#else
	#include <unistd.h>
	#define GetCurrentDir getcwd
#endif

using namespace std;

namespace DeltaEngine {
	namespace Utils {

		DELTAENGINE_API Types::timestamp getSystemTime();
		DELTAENGINE_API Types::timestamp getUTCTime();

		DELTAENGINE_API Types::time timestampToTime(const Types::timestamp& t);
		DELTAENGINE_API Types::date timestampToDate(const Types::timestamp& t);

		DELTAENGINE_API string getCurrentPath();

		DELTAENGINE_API vector<string> splitString(const string& str, char delimiter);

		// Console utilities
		DELTAENGINE_API void gotoxy(int x, int y);
		DELTAENGINE_API void setConsoleColor(int color);
	}
}