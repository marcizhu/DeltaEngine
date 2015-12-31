#pragma once

#include <vector>

#include "buffer.h"
#include "indexBuffer.h"
#include "vertexArray.h"
#include "maths.h"
#include "shader.h"

namespace DeltaEngine {
	namespace Graphics {

		class Renderable2D
		{
		private:
			void setUVDefaults()
			{
				UV.push_back(Maths::Vector2D(0, 0));
				UV.push_back(Maths::Vector2D(0, 1));
				UV.push_back(Maths::Vector2D(1, 1));
				UV.push_back(Maths::Vector2D(1, 0));
			}

		protected:
			Maths::Vector2D position;
			Maths::Vector2D size;
			Types::Color color;
			std::vector<Maths::Vector2D> UV;

			Renderable2D() { setUVDefaults(); }

		public:
			Renderable2D(Maths::Vector2D& position, Maths::Vector2D& size, Types::Color color) : position(position), size(size), color(color) { setUVDefaults(); }

			virtual ~Renderable2D() {}

			inline const Maths::Vector2D& getPosition() const { return position; }
			inline const Maths::Vector2D& getSize() const { return size; }
			inline const Types::Color& getColor() const { return color; }
			inline const std::vector<Maths::Vector2D>& getUV() const { return UV; }

			inline void moveTo(float x, float y) { position.x = x; position.y = y; }
			inline void move(float dx, float dy) { position.x += dx; position.y += dy; }
		};
		
	}
}