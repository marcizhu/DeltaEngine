#pragma once

#include "DeltaEngine.h"
#include "renderable2d.h"
#include "types.h"

namespace DeltaEngine {
	namespace Graphics {

		class SimpleRenderable2D : public Renderable2D
		{
		private:
			VertexArray* vertexArray;
			IndexBuffer* indexBuffer;
			Shader& shader;

		public:
			DELTAENGINE_API SimpleRenderable2D(float x, float y, float width, float height, const Types::Color& color, Shader& shader);
			DELTAENGINE_API ~SimpleRenderable2D();

			DELTAENGINE_API inline const VertexArray* getVertexArray() const { return vertexArray; }
			DELTAENGINE_API inline const IndexBuffer* getIndexBuffer() const { return indexBuffer; }

			DELTAENGINE_API inline Shader& getShader() const { return shader; }
		};

	}
}