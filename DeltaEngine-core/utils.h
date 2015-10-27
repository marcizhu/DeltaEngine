#pragma once

#ifndef __DELTAENGINE_UTILS__
#define __DELTAENGINE_UTILS__

#include <Windows.h>
#include <stdio.h>

#include"DeltaEngine.h"

namespace DeltaEngine {
	namespace Utils {

		typedef struct _timestamp {
			WORD Year;
			WORD Month;
			WORD DayOfWeek;
			WORD Day;
			WORD Hour;
			WORD Minute;
			WORD Second;
			WORD Milliseconds;
		} timestamp;

		typedef struct _date {
			WORD Year;
			WORD Month;
			WORD DayOfWeek;
			WORD Day;
		} date;

		typedef struct _time {
			WORD Hour;
			WORD Minute;
			WORD Second;
			WORD Milliseconds;
		} time;

		DELTAENGINE_API timestamp getSystemTime();
		DELTAENGINE_API timestamp getUTCTime();

		DELTAENGINE_API time timestampToTime(const timestamp& t);
		DELTAENGINE_API date timestampToDate(const timestamp& t);
	}
}

#endif