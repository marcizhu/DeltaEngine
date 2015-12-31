#include "batchRenderer2d.h"
#include "types.h"

namespace DeltaEngine {
	namespace Graphics {

		// FIXME: Optimize this using vertexArrays, Buffers and IndexBuffers

		BatchRenderer2D::BatchRenderer2D() : Renderer2D()
		{
			glGenVertexArrays(1, &vertexArray);
			glGenBuffers(1, &vertexBuffer);

			glBindVertexArray(vertexArray);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_UV_INDEX);
			glEnableVertexAttribArray(SHADER_COLOR_INDEX);

			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
			glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::uv)));
			glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));
			
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			GLuint* indices = new GLuint[RENDERER_INDICES_SIZE];

			int offset = 0;
			for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
			{
				indices[i] = offset + 0;
				indices[i + 1] = offset + 1;
				indices[i + 2] = offset + 2;

				indices[i + 3] = offset + 2;
				indices[i + 4] = offset + 3;
				indices[i + 5] = offset + 0;

				offset += 4;
			}

			indexBuffer = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

			glBindVertexArray(0);
		}

		BatchRenderer2D::~BatchRenderer2D()
		{
			delete indexBuffer;
			glDeleteBuffers(1, &vertexBuffer);
		}

		void BatchRenderer2D::begin()
		{
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			buffer = (Types::VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void BatchRenderer2D::submit(const Renderable2D* renderable)
		{
			const Maths::Vector2D& position = renderable->getPosition();
			const Maths::Vector2D& size = renderable->getSize();
			Types::Color color = renderable->getColor();
			const std::vector<Maths::Vector2D>& uv = renderable->getUV();

			// FIXME: this works? Test SimpleRenderer
			color.A = 255 - color.A;

			buffer->vertex = *transformationStackTop * position;
			buffer->uv = uv[0];
			buffer->color = color;
			buffer++;
			
			buffer->vertex = *transformationStackTop * Maths::Vector2D(position.x, position.y + size.y);
			buffer->uv = uv[1];
			buffer->color = color;
			buffer++;
			
			buffer->vertex = *transformationStackTop * Maths::Vector2D(position.x + size.x, position.y + size.y);
			buffer->uv = uv[2];
			buffer->color = color;
			buffer++;
			
			buffer->vertex = *transformationStackTop * Maths::Vector2D(position.x + size.x, position.y);
			buffer->uv = uv[3];
			buffer->color = color;
			buffer++;

			indexCount += 6;
		}

		void BatchRenderer2D::end()
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void BatchRenderer2D::flush()
		{
			glBindVertexArray(vertexArray);
			indexBuffer->bind();

			glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, NULL);

			indexBuffer->unbind();
			glBindVertexArray(0);

			indexCount = 0;
		}

	}
}
