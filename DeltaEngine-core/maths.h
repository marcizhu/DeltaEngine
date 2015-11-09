#pragma once

#ifndef __DELTAENGINE_MATHS__
#define __DELTAENGINE_MATHS__

const double PI = 3.14159265358979323846;

namespace DeltaEngine {
	namespace Maths {

		inline float toRadians(float degrees)
		{
			return degrees * (PI / 180.0f);
		}

	}
}

#endif