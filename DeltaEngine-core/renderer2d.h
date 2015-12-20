#pragma once

#include <deque>

#include "DeltaEngine.h"
#include "renderable2d.h"

namespace DeltaEngine {
	namespace Graphics {

		class Renderer2D
		{
		public:
			DELTAENGINE_API virtual void submit(const Renderable2D* renderable) = 0;
			//DELTAENGINE_API virtual void submit(std::deque<const Renderable2D*> queue) = 0;
			DELTAENGINE_API virtual void flush() = 0;
		};

	}
}
