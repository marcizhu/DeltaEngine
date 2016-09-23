#pragma once

#include <string>
#include <vector>
#include <iomanip>

#include "internal.h"
#include "types.h"

#include "physicsRenderable2D.h"

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

		DELTAENGINE_API Types::timestamp getBuildTime();
		DELTAENGINE_API Types::timestamp getSystemTime();
		DELTAENGINE_API Types::timestamp getUTCTime();

		DELTAENGINE_API void printBuildTime();

		DELTAENGINE_API Types::time timestampToTime(const Types::timestamp& t);
		DELTAENGINE_API Types::date timestampToDate(const Types::timestamp& t);

		DELTAENGINE_API string getCurrentPath();

		DELTAENGINE_API inline string precision_to_string(const float val, char n);

		DELTAENGINE_API inline void printDate(const Types::date& date);
		DELTAENGINE_API inline void printTime(const Types::time& time);
		DELTAENGINE_API inline void printTimestamp(const Types::timestamp& t);

		template<typename T>
		string toHex(T i)
		{
			stringstream stream;

			stream << "0x" << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << std::uppercase << i;

			return stream.str();
		}

		template<typename T>
		T random(T min, T max)
		{
			T value = rand() % (max - min);

			return (value + min);
		}

		DELTAENGINE_API vector<string> splitString(const string& str, char delimiter);

		// Console utilities
		DELTAENGINE_API void gotoxy(int x, int y);
		DELTAENGINE_API void setConsoleColor(int color);
		DELTAENGINE_API void clearScreen();

		DELTAENGINE_API inline Physics::PhysicsRenderable2D* toPhysicsRenderable(const Graphics::Renderable2D* renderable);
	}
}