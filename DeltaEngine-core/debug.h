#pragma once

#ifndef __DELTAENGINE_DEBUG__
#define __DELTAENGINE_DEBUG__

#include "DeltaEngine.h"

namespace DeltaEngine {
	namespace Debug {

		class Debug {
		public:
			DELTAENGINE_API static void checkErrors();
		};

	}
}

#endif