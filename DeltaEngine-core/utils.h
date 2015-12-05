#pragma once

#ifndef __DELTAENGINE_UTILS__
#define __DELTAENGINE_UTILS__

#include <Windows.h>
#include <stdio.h>
#include <string>

#include "DeltaEngine.h"
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
		
		// Console utilities
		DELTAENGINE_API void gotoxy(int x, int y);
		DELTAENGINE_API void setConsoleColor(int color);

		// Math utilities
		template<typename T>
		inline T constrain(T val, T min, T max) { return val > max ? max : val < min ? min : val; };
		
		template<typename T>
		inline bool isBetween(T x, T min, T max) { return x < max ? x > min ? true : false : false; }
	}
}

#endif