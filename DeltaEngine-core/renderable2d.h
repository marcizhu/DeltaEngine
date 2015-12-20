#pragma once

#include "buffer.h"
#include "indexBuffer.h"
#include "vertexArray.h"
#include "maths.h"
#include "shader.h"

namespace DeltaEngine {
	namespace Graphics {

		class Renderable2D
		{
		protected:
			Maths::Vector2D position;
			Maths::Vector2D size;
			Types::Color color;

		public:
			Renderable2D(Maths::Vector2D& position, Maths::Vector2D& size, Types::Color color) : position(position), size(size), color(color) {}

			virtual ~Renderable2D() {}

			inline const Maths::Vector2D& getPosition() const { return position; }
			inline const Maths::Vector2D& getSize() const { return size; }
			inline const Types::Color& getColor() const { return color; }

			inline void moveTo(float x, float y) { position.x = x; position.y = y; }
			inline void move(float dx, float dy) { position.x += dx; position.y += dy; }
		};

		
	}
}