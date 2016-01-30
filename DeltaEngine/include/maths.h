#pragma once

#include <vector>

#include "internal.h"
#include "types.h"

const double PI = 3.14159265358979323846;
const double PHI = (sqrt(5) + 1) / 2; //Golden ratio

using namespace DeltaEngine::Types;

namespace DeltaEngine {
	namespace Maths {

		// Math utilities

		DELTAENGINE_API bool isPrime(uint32 n);

		DELTAENGINE_API uint32 findPrime(uint32 start);

		DELTAENGINE_API std::vector<uint32> factorialDecomposition(uint32 number);

		inline float toRadians(float degrees) { return degrees * (float)(PI / 180.0f); }
		
		inline signed int sign(float value) { return (value > 0) - (value < 0); }
		
		template<typename T>
		inline T constrain(T val, T min, T max) { return val > max ? max : val < min ? min : val; };

		template<typename T>
		inline bool isBetween(T x, T min, T max) { return x <= max ? x = > min ? true : false : false; }

		//template<typename T>
		//inline T& max(T& first, T& second) { return first > second ? first : second; }

		//template<typename T>
		//inline T& min(T& first, T& second) { return first < second ? first : second; }
	}
}