#pragma once

#include <string>

#include "DeltaEngine.h"
#include "vector2d.h"
#include "types.h"

namespace DeltaEngine {
	namespace Graphics {

		class Renderable2D;

		class Renderer2D
		{
		public:
			DELTAENGINE_API virtual void begin() { };
			DELTAENGINE_API virtual void submit(const Renderable2D* renderable) = 0;
			DELTAENGINE_API virtual void end() { };
			DELTAENGINE_API virtual void flush() = 0;

			DELTAENGINE_API virtual void drawString(const std::string& text, const Maths::Vector2D& position, const Types::Color& color) {}

			//TODO: REMOVE THIS!
			DELTAENGINE_API virtual void drawLine(const Maths::Vector2D& start, const Maths::Vector2D& end, unsigned int color) { };
		};

	}
}
