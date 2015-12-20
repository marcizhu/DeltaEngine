#pragma once

#include "DeltaEngine.h"
#include "types.h"

namespace DeltaEngine {
	namespace Debug {

		DELTAENGINE_API void checkErrors();
		DELTAENGINE_API void dump(const void* object, Types::uint32 size, int color = 0x03);

	}
}