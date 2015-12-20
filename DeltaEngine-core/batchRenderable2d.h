#pragma once

#include "renderable2d.h"
#include "types.h"

namespace DeltaEngine {
	namespace Graphics {

		class BatchRenderable2D : public Renderable2D
		{
		private:

		public:
			BatchRenderable2D(float x, float y, float width, float height, Types::Color color) 
				: Renderable2D(Maths::Vector2D(x, y), Maths::Vector2D(width, height), color) { };
		};
	}
}