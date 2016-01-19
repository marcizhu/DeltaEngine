#pragma once

#include <string>

#include "DeltaEngine.h"
#include "renderable2d.h"
#include "renderer2d.h"
#include "vector2d.h"
#include "vector4d.h"
#include "types.h"

namespace DeltaEngine {
	namespace Graphics {

		class Label : public Renderable2D
		{
		public:
			std::string text;
			Maths::Vector2D& position;
			float x, y;

		public:
			DELTAENGINE_API Label(std::string text, float x, float y, Types::Color color);
			DELTAENGINE_API void submit(Renderer2D* renderer) const { renderer->drawString(text, position, color); };
		};

	}
}