#include "string.h"

namespace DeltaEngine {
	namespace Utils {

		String::String(std::string string)
		{
			const char* s = string.c_str();

			while (*s)
			{
				data.push_back(s);
				s++;
			}
		}

		String::String(const char * string)
		{
			while (*string)
			{
				data.push_back(string);
				string++;
			}
		}

	}
}