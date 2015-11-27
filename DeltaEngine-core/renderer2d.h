#pragma once

#include <deque>

#include "DeltaEngine.h"
#include "renderable2d.h"

namespace DeltaEngine {
	namespace Graphics {

		class Renderer2D
		{
		private:
			std::deque<const Renderable2D*> renderQueue;

		public:
			DELTAENGINE_API inline void submit(const Renderable2D* renderable) { renderQueue.push_back(renderable); };
			DELTAENGINE_API inline void submit(std::deque<const Renderable2D*> queue) { renderQueue = queue; };
			DELTAENGINE_API void flush();

			DELTAENGINE_API inline const std::deque<const Renderable2D*> getActualQueue() { return renderQueue; };
		};

	}
}
