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
			void push(const T& val) { data.push_back(val); };
			void pop() { if (!data.empty()) data.pop_back(); };

			const T& top() const { return data.back(); };
			const T& base() const { return data.front(); };

			uint32 size() const { return data.size(); };

			const std::list<T> getStack() const { return this->data; };

			const T& operator[](uint32 idx) const { return data[idx]; };
			const void operator=(const Stack& other) const { data = other.getStack(); };
		};

	}
}