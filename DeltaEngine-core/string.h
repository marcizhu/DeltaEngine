#pragma once

#include <string>
#include <vector>

#include "types.h"

namespace DeltaEngine {
	namespace Utils {

		class String {
		private:
			std::vector<const char*> data;

		public:
			String() { };
			String(std::string string);
			String(const char* string);

			Types::uint32 size() const { return data.size(); };
		};

	}
}