#include <vector>

#include "renderable2d.h"
#include "vector2d.h"
#include "shader.h"
#include "types.h"

namespace DeltaEngine {
	namespace Graphics {

		Renderable2D::Renderable2D(const Maths::Vector2D& position, int zorder, const Maths::Vector2D& size, const Types::Color& color, Shader& shader)
			: zorder(zorder), size(size), color(color), shader(shader), multiplePositions(false)
		{
			positions.push_back(position);

			vertexArray = new VertexArray();
			GLfloat vertices[] =
			{
				     0,      0, 0,
				     0, size.y, 0,
				size.x, size.y, 0,
				size.x,      0, 0
			};

			float fr = color.R / 255;
			float fg = color.G / 255;
			float fb = color.B / 255;
			float fa = color.A / 255;

			GLfloat colors[] =
			{
				fr, fg, fb, fa,
				fr, fg, fb, fa,
				fr, fg, fb, fa,
				fr, fg, fb, fa,
			};

			vertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
			vertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);

			GLushort indices[] = { 0, 1, 2, 2, 3, 0 };
			indexBuffer = new IndexBuffer(indices, 6);
		}

		Renderable2D::~Renderable2D()
		{
			delete vertexArray;
			delete indexBuffer;
		}

		Renderable2D::Renderable2D(const std::vector<Maths::Vector2D>& positions, int zorder, const Maths::Vector2D& size, const Types::Color& color, Shader& shader)
			: zorder(zorder), size(size), color(color), shader(shader), multiplePositions(true)
		{
			this->positions = positions;
			this->zorder = zorder;

			vertexArray = new VertexArray();
			GLfloat vertices[] =
			{
				     0,      0, 0,
				     0, size.y, 0,
				size.x, size.y, 0,
				size.x,      0, 0
			};

			float fr = color.R / 255;
			float fg = color.G / 255;
			float fb = color.B / 255;
			float fa = color.A / 255;

			GLfloat colors[] =
			{
				fr, fg, fb, fa,
				fr, fg, fb, fa,
				fr, fg, fb, fa,
				fr, fg, fb, fa,
			};

			vertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
			vertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);

			GLushort indices[] = { 0, 1, 2, 2, 3, 0 };
			indexBuffer = new IndexBuffer(indices, 6);
		}

	}
}