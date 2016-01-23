#pragma once

#include <deque>

#include "DeltaEngine.h"
#include "renderable2d.h"
#include "renderer2d.h"
#include "simpleRenderable2d.h"
#include "types.h"

using namespace DeltaEngine::Types;

namespace DeltaEngine {
	namespace Graphics {

		class SimpleRenderer2D : public Renderer2D
		{
		private:
			std::deque<const SimpleRenderable2D*> renderQueue;

		public:
			SimpleRenderer2D() : Renderer2D() {};
			DELTAENGINE_API inline void submit(const Renderable2D* renderable) override { renderQueue.push_back((SimpleRenderable2D*)renderable); };
			DELTAENGINE_API inline void submit(std::deque<const SimpleRenderable2D*> queue) { renderQueue = queue; };
			DELTAENGINE_API void flush() override;

			DELTAENGINE_API inline const std::deque<const SimpleRenderable2D*> getCurrentQueue() { return renderQueue; };
		};

	}
}