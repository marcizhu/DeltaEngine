#pragma once

#include <vector>

#include "internal.h"
#include "types.h"

#if defined(min) || defined(max)
#	undef min
#	undef max
#endif

const double PI = 3.14159265358979323846;
const double PHI = (sqrt(5) + 1) / 2; //Golden ratio

using namespace DeltaEngine::Types;

namespace DeltaEngine {
	namespace Maths {

		// Math utilities

		DELTAENGINE_API bool isPrime(uint32 n);

		DELTAENGINE_API uint32 findPrime(uint32 start);

		DELTAENGINE_API std::vector<uint32> factorialDecomposition(uint32 number);

		DELTAENGINE_API inline double nlog(uint32 base, double value);

		inline float toRadians(float degrees) { return degrees * (float)(PI / 180.0f); }
		inline float toDegrees(float radians) { return radians * (float)(180.0f / PI); }

		inline signed int sign(float value) { return (value > 0) - (value < 0); }

		template<typename T>
		inline T constrain(T val, T min, T max) { return val > max ? max : val < min ? min : val; }

		template<typename T>
		inline bool isBetween(T x, T min, T max) { return x <= max ? x >= min ? true : false : false; }

		inline bool isPowOf2(int n) { return (n & (n - 1)) == 0; }

		template<typename T>
		inline uint32 nlen(T n) { return (uint32)(log10(n) + 1); }

		template<typename T>
		inline T min(T first, T second) { return first > second ? second : first; }

		template<typename T>
		inline T max(T first, T second) { return first > second ? first : second; }

		//template<typename T>
		//inline T& max(T& first, T& second) { return first > second ? first : second; }

		//template<typename T>
		//inline T& min(T& first, T& second) { return first < second ? first : second; }

		double __forceinline __declspec(naked) __fastcall sqrt(double n)
		{
			_asm
			{
				fld qword ptr[esp + 4]
				fsqrt
				ret 8
			}
		}

		float __forceinline __declspec(naked) __fastcall sqrt(float n)
		{
			_asm
			{
				fld dword ptr[esp + 4]
				fsqrt
				ret 4
			}
		}

		// from "Quake III Arena" :)
		float __forceinline rsqrt(float number)
		{
			long i;
			float x2, y;
			const float threehalfs = 1.5F;

			x2 = number * 0.5F;
			y = number;
			i = *(long *)&y;							// evil floating point bit level hacking
			i = 0x5f3759df - (i >> 1);					// what the fuck?
			y = *(float *)&i;
			y = y * (threehalfs - (x2 * y * y));		// 1st iteration
			y = y * (threehalfs - (x2 * y * y));		// 2nd iteration, this can be removed

			return y;
		}

	}
}