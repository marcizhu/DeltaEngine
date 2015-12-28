#include "simpleRenderable2d.h"
#include "types.h"
#include "vector2d.h"

namespace DeltaEngine {
	namespace Graphics {

		SimpleRenderable2D::SimpleRenderable2D(float x, float y, float width, float height, const Types::Color& color, Shader& shader)
			: Renderable2D(Maths::Vector2D(x, y), Maths::Vector2D(width, height), color), shader(shader)
		{
			vertexArray = new VertexArray();

			GLfloat vertices[] =
			{
					0,		0, 0,
					0, height, 0,
				width, height, 0,
				width,		0, 0
			};

			float fr = color.R / 255.0f;
			float fg = color.G / 255.0f;
			float fb = color.B / 255.0f;
			float fa = color.A / 255.0f;

			GLfloat colors[] =
			{
				fr, fg, fb, fa,
				fr, fg, fb, fa,
				fr, fg, fb, fa,
				fr, fg, fb, fa
			};

			vertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
			vertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);

			GLushort indices[] = { 0, 1, 2, 2, 3, 0 };
			indexBuffer = new IndexBuffer(indices, 6);
		}

		SimpleRenderable2D::~SimpleRenderable2D()
		{
			delete vertexArray;
			delete indexBuffer;
		}

	}
}