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
			void push(const T& val) { data.push_front(val); };
			void pop() { if (!data.empty()) data.pop_front(); };

			const T& front() const { return data.front(); };
			const T& back() const { return data.back(); };

			uint32 size() const { return data.size(); };

			const std::list<T> getStack() const { return this->data; };

			const T& operator[](Types::uint32 idx) const { return data[idx]; };
			const void operator=(const Stack& other) const { data = other.getStack(); };
		};

	}
}