#pragma once

#ifndef __DELTAENGINE_RENDERABLE_2D__
#define __DELTAENGINE_RENDERABLE_2D__

#ifdef OLD_RENDERABLE2D
#include <vector>

#include "buffer.h"
#include "indexBuffer.h"
#include "vertexArray.h"
#include "vector2d.h"
#include "shader.h"
#include "types.h"
#else
#include "buffer.h"
#include "indexBuffer.h"
#include "vertexArray.h"
#include "maths.h"
#include "shader.h"
#endif

namespace DeltaEngine {
	namespace Graphics {

#ifdef OLD_RENDERABLE_2D
		class Renderable2D
		{
		protected:
			Maths::Vector2D size;
			Types::Color color;

			VertexArray* vertexArray;
			IndexBuffer* indexBuffer;
			Shader& shader;

			std::vector<Maths::Vector2D> positions;

			Types::schar8 zorder;

		public:
			DELTAENGINE_API Renderable2D(const Maths::Vector2D& position, int zorder, const Maths::Vector2D& size, const Types::Color& color, Shader& shader);
			DELTAENGINE_API Renderable2D(const std::vector<Maths::Vector2D>& positions, int zorder, const Maths::Vector2D& size, const Types::Color& color, Shader& shader);
			DELTAENGINE_API virtual ~Renderable2D();

			DELTAENGINE_API inline const VertexArray* getVertexArray() const { return vertexArray; };
			DELTAENGINE_API inline const IndexBuffer* getIndexBuffer() const { return indexBuffer; };

			DELTAENGINE_API inline Shader& getShader() const { return shader; };

			DELTAENGINE_API inline const Maths::Vector2D& getFirstPosition() const { return positions[0]; };
			DELTAENGINE_API inline const std::vector<Maths::Vector2D> getPositions() const { return positions; };
			DELTAENGINE_API inline const Maths::Vector2D& getSize() const { return size; };
			DELTAENGINE_API inline const Types::Color& getColor() const { return color; };

			DELTAENGINE_API inline void moveTo(float x, float y, Types::ushort16 index = 0) { positions[index].x = x; positions[index].y = y; }
			DELTAENGINE_API inline void move(float dx, float dy, Types::ushort16 index = 0) { positions[index].x += dx; positions[index].y += dy; }

			DELTAENGINE_API inline const int getZorder() const { return zorder; };
		};
#else
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
		};
#endif

		
	}
}

#endif