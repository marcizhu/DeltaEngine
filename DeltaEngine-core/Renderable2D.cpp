#include <vector>

#include "renderable2d.h"
#include "vector2d.h"
#include "vector3d.h"
#include "vector4d.h"
#include "types.h"

namespace DeltaEngine {
	namespace Graphics {

		Renderable2D::Renderable2D(Maths::Vector3D position, Maths::Vector2D size, Types::Color color, Shader& shader)
			: position(position), size(size), color(color), shader(shader), multiplePositions(false)
		{
			vertexArray = new VertexArray();
			GLfloat vertices[] =
			{
				     0,      0, 0,
				     0, size.y, 0,
				size.x, size.y, 0,
				size.x,      0, 0
			};

			GLfloat colors[] =
			{
				color.R, color.G, color.B, color.A,
				color.R, color.G, color.B, color.A,
				color.R, color.G, color.B, color.A,
				color.R, color.G, color.B, color.A,
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

		Renderable2D::Renderable2D(std::vector<Maths::Vector2D>& positions, int zorder, Maths::Vector2D size, Types::Color color, Shader& shader)
			: size(size), color(color), shader(shader), multiplePositions(true)
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

			GLfloat colors[] =
			{
				color.R, color.G, color.B, color.A,
				color.R, color.G, color.B, color.A,
				color.R, color.G, color.B, color.A,
				color.R, color.G, color.B, color.A,
			};

			vertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
			vertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);

			GLushort indices[] = { 0, 1, 2, 2, 3, 0 };
			indexBuffer = new IndexBuffer(indices, 6);
		}
	}
}