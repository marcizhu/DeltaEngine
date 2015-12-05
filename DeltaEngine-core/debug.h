#pragma once

#ifndef __DELTAENGINE_DEBUG__
#define __DELTAENGINE_DEBUG__

#include "DeltaEngine.h"
#include "types.h"

namespace DeltaEngine {
	namespace Debug {

		class Debug {
		public:
			DELTAENGINE_API static void checkErrors();
			DELTAENGINE_API static void dump(void* object, Types::uint32 size);
		};

	}
}

#endif