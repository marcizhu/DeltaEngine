#pragma once

#ifndef __DELTAENGINE_MATHS__
#define __DELTAENGINE_MATHS__

#include <math.h>

#include <iostream>

const double PI = 3.14159265358979323846;
const double PHI = (sqrt(5) + 1) / 2; //Golden ratio

namespace DeltaEngine {
	namespace Maths {

		inline float toRadians(float degrees)
		{
			return degrees * (PI / 180.0f);
		}

		bool isPrime(unsigned int n)
		{
			//prime numbers can only be divided by 1 & themselves
			if (n <= 1) return false;
			for (unsigned int i = 1; i < n; i++)
			{
				if ((n % i == 0) && (i != 1)) return false;
			}
			return true;
		}

		unsigned int findPrime(unsigned int start)
		{
			while (start)
			{
				if (isPrime(start)) return start;
				start++;
			}

			return start;
		}

		void factorialDecomposition(unsigned int number)
		{
			std::cout << "Decomposition of " << number << ": ";
			unsigned int prime = 1;
			while (number != 1)
			{
				prime = findPrime(prime);
				if (number % prime == 0)
				{
					std::cout << prime;
					number /= prime;
					if (number > 1) std::cout << " * ";
				} else
				{
					while (number % prime != 0)
					{
						prime = findPrime(prime + 1);
					}

					std::cout << prime;
					number /= prime;
					if (number > 1) std::cout << " * ";
				}
			}

			std::cout << std::endl << std::endl;
		}

	}
}

#endif