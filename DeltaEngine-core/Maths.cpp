#include "maths.h"
#include "types.h"

//using namespace DeltaEngine::Types;

namespace DeltaEngine {
	namespace Maths {

		bool isPrime(Types::uint32 n)
		{
			//prime numbers can only be divided by 1 & themselves
			if (n <= 1) return false;

			for (Types::uint32 i = 1; i < n; i++)
				if ((n % i == 0) && (i != 1)) return false;

			return true;
		}

		Types::uint32 findPrime(Types::uint32 start)
		{
			while (start)
			{
				if (isPrime(start)) return start;
				start++;
			}

			return start;
		}

		std::vector<Types::uint32> factorialDecomposition(Types::uint32 number)
		{
			Types::uint32 prime = 1;
			std::vector<Types::uint32> temp;

			while (number != 1)
			{
				prime = findPrime(prime);

				if (number % prime == 0)
				{
					temp.push_back(prime);
					number /= prime;
				} else
				{
					while (number % prime != 0) prime = findPrime(prime + 1);

					temp.push_back(prime);
					number /= prime;
				}
			}

			return temp;
		}
	}
}