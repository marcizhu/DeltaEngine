#pragma once

#ifndef __DELTAENGINE_RENDERABLE_2D__
#define __DELTAENGINE_RENDERABLE_2D__

#include <vector>

#include "buffer.h"
#include "indexBuffer.h"
#include "vertexArray.h"
#include "vector2d.h"
#include "vector3d.h"
#include "vector4d.h"
#include "shader.h"
#include "types.h"

namespace DeltaEngine {
	namespace Graphics {

		class Renderable2D
		{
		protected:
			Maths::Vector3D position;
			Maths::Vector2D size;
			Types::Color color;

			VertexArray* vertexArray;
			IndexBuffer* indexBuffer;
			Shader& shader;

			std::vector<Maths::Vector2D> positions;

			bool multiplePositions;
			int zorder;

		public:
			DELTAENGINE_API Renderable2D(Maths::Vector3D position, Maths::Vector2D size, Types::Color color, Shader& shader);
			DELTAENGINE_API Renderable2D(std::vector<Maths::Vector2D>& positions, int zorder, Maths::Vector2D size, Types::Color color, Shader& shader);

			DELTAENGINE_API virtual ~Renderable2D();

			DELTAENGINE_API inline const VertexArray* getVertexArray() const { return vertexArray; };
			DELTAENGINE_API inline const IndexBuffer* getIndexBuffer() const { return indexBuffer; };

			DELTAENGINE_API inline Shader& getShader() const { return shader; };

			DELTAENGINE_API inline const Maths::Vector3D& getPosition() const { return position; };
			DELTAENGINE_API inline const std::vector<Maths::Vector2D> getMultiplePositions() const { return positions; };
			DELTAENGINE_API inline const Maths::Vector2D& getSize() const { return size; };
			DELTAENGINE_API inline const Types::Color& getColor() const { return color; };

			DELTAENGINE_API inline const bool hasMultiplePositions() const { return multiplePositions; };
			DELTAENGINE_API inline const int getZorder() const { return zorder; };
		};


	}
}

#endif