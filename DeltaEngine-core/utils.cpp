#include "utils.h"

namespace DeltaEngine {
	namespace Utils {

		timestamp getSystemTime()
		{
			SYSTEMTIME st;
			GetLocalTime(&st);

			timestamp ret;
			ret.Milliseconds = st.wMilliseconds;
			ret.Second = st.wSecond;
			ret.Minute = st.wMinute;
			ret.Hour = st.wHour;
			ret.Day = st.wDay;
			ret.DayOfWeek = st.wDayOfWeek;
			ret.Month = st.wMonth;
			ret.Year = st.wYear;

			return ret;
		}

		timestamp getUTCTime()
		{
			SYSTEMTIME st;
			GetSystemTime(&st);

			timestamp ret;
			ret.Milliseconds = st.wMilliseconds;
			ret.Second = st.wSecond;
			ret.Minute = st.wMinute;
			ret.Hour = st.wHour;
			ret.Day = st.wDay;
			ret.DayOfWeek = st.wDayOfWeek;
			ret.Month = st.wMonth;
			ret.Year = st.wYear;

			return ret;
		}

		time timestampToTime(const timestamp& t)
		{
			time ret;
			ret.Milliseconds = t.Milliseconds;
			ret.Second = t.Second;
			ret.Minute = t.Minute;
			ret.Hour = t.Hour;

			return ret;
		}

		date timestampToDate(const timestamp& t)
		{
			date ret;
			ret.Day = t.Day;
			ret.DayOfWeek = t.DayOfWeek;
			ret.Month = t.Month;
			ret.Year = t.Year;

			return ret;
		}

	}
}