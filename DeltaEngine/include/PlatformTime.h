#pragma once

#include "types.h"

namespace DeltaEngine {
	namespace Internal {

#ifdef _WIN32
#include <Windows.h>

		static inline Types::timestamp getSystemTime()
		{
			SYSTEMTIME st;
			GetLocalTime(&st);

			Types::timestamp ret;
			memcpy_s(&ret, sizeof(ret), &st, sizeof(ret));
			return ret;
		}

		static inline Types::timestamp getUTCTime()
		{
			SYSTEMTIME st;
			GetSystemTime(&st);

			Types::timestamp ret;
			memcpy_s(&ret, sizeof(ret), &st, sizeof(ret));
			return ret;
		}

#else
#error("This platform is not supported")
#endif

	}
}