#pragma once

#include "renderable2d.h"
#include "types.h"
#include "vector2d.h"
#include "texture.h"
#include "sprite.h"

namespace DeltaEngine {
	namespace Graphics {

		class BatchRenderable2D : public Renderable2D
		{
		public:
			BatchRenderable2D(float x, float y, float width, float height, Types::Color color) 
				: Renderable2D(Maths::Vector2D(x, y), Maths::Vector2D(width, height), color)
			{ this->texture = nullptr; };

			BatchRenderable2D(float x, float y, float width, float height, Types::uint32 color)
				: Renderable2D(Maths::Vector2D(x, y), Maths::Vector2D(width, height), color)
			{ this->texture = nullptr; };
			
			BatchRenderable2D(float x, float y, float width, float height, Texture* texture)
				: Renderable2D(Maths::Vector2D(x, y), Maths::Vector2D(width, height), Types::Color(255, 0, 255, 255))
			{ this->texture = texture; }

			BatchRenderable2D(float x, float y, float width, float height, Sprite sprite)
				: Renderable2D(Maths::Vector2D(x, y), Maths::Vector2D(width, height), Types::Color(255, 0, 255, 255))
			{ this->texture = nullptr; this->sprites = sprite; }
		};
	}
}