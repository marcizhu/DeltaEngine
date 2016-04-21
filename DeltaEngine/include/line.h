#pragma once

#include "renderable2d.h"
#include "vector2d.h"
#include "types.h"

namespace DeltaEngine {
	namespace Graphics {

		class Line : public Renderable2D
		{
		private:
			float x0, y0, x1, y1;
			float thickness;
			Types::uint32 color;

		public:
			Line(float x0, float y0, float x1, float y1, float thickness, Types::Color color)
				: Renderable2D()
			{
				this->x0 = x0;
				this->y0 = y0;
				this->x1 = x1;
				this->y1 = y1;
				this->thickness = thickness;
				this->color = color.getABGRColor();
			}

			Line(float x0, float y0, float x1, float y1, float thickness, Types::uint32 color)
				: Renderable2D()
			{
				this->x0 = x0;
				this->y0 = y0;
				this->x1 = x1;
				this->y1 = y1;
				this->thickness = thickness;
				this->color = color;
			}

			void submit(Renderer2D* renderer) const override { renderer->drawLine(Maths::Vector2D(x0, y0), Maths::Vector2D(x1, y1), thickness, color); }
		};

	}
}