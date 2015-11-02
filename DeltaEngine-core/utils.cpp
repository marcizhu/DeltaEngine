#include <string>

#include "utils.h"

using namespace std;

namespace DeltaEngine {
	namespace Utils {

		timestamp getSystemTime()
		{
			SYSTEMTIME st;
			GetLocalTime(&st);

			timestamp ret;
			memcpy_s(&ret, sizeof(ret), &st, sizeof(ret));
			return ret;
		}

		timestamp getUTCTime()
		{
			SYSTEMTIME st;
			GetSystemTime(&st);

			timestamp ret;
			memcpy_s(&ret, sizeof(ret), &st, sizeof(ret));
			return ret;
		}

		time timestampToTime(const timestamp& t)
		{
			time ret;
			memcpy_s(&ret, sizeof(ret), &t.Hour, sizeof(ret));
			return ret;
		}

		date timestampToDate(const timestamp& t)
		{
			date ret;
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
	}
}