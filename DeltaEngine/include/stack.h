#pragma once

#include <list>

#include "types.h"

using namespace DeltaEngine::Types;

namespace DeltaEngine {
	namespace Utils {

		template<typename T>
		class Stack {
		private:
			std::list<T> data;

		public:
			inline const T* push(const T& val) { data.push_back(val); return &data.back(); };
			inline const T* pop() { if (!data.empty()) data.pop_back(); return &data.back(); };

			inline const T& top() const { return data.back(); };
			inline const T& base() const { return data.front(); };

			inline uint32 size() const { return data.size(); };

			inline const std::list<T>& getStack() const { return this->data; };

			inline const T& operator[](uint32 idx) const { return data[idx]; };
			inline const void operator=(const Stack& other) const { data = other.getStack(); };
		};

	}
}