#pragma once

#include "DeltaEngine.h"
#include "renderable2d.h"
#include "renderer2d.h"
#include "types.h"

using namespace DeltaEngine::Types;

namespace DeltaEngine {
	namespace Graphics {

		class SimpleRenderer2D : public Renderer2D
		{
		public:
			DELTAENGINE_API inline void submit(const Renderable2D* renderable) override { renderQueue.push_back(renderable); };
			DELTAENGINE_API inline void submit(std::deque<const Renderable2D*> queue) override { renderQueue = queue; };
			DELTAENGINE_API void flush() override;

			//sorts by Z order
			DELTAENGINE_API void sort(schar8 index = 0);

			DELTAENGINE_API inline const std::deque<const Renderable2D*> getActualQueue() { return renderQueue; };
		};

	}
}