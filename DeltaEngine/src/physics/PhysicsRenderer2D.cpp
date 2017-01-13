#include "physicsRenderer2d.h"
#include "types.h"
#include "maths.h"
#include "log.h"
#include "memoryManager.h"
#include "matrix4.h"
#include "physicsRenderable2d.h"

namespace DeltaEngine {
	namespace Physics {

		// FIXME: Optimize this using Buffers
		// TODO: Rewrite Buffer.cpp

		PhysicsRenderer2D::PhysicsRenderer2D() : Graphics::Renderer2D(), indexCount(0)
		{
			vertexArray = NEW Graphics::VertexArray();
			glGenBuffers(1, &vertexBuffer);

			vertexArray->bind();
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_UV_INDEX);
			glEnableVertexAttribArray(SHADER_TID_INDEX);
			glEnableVertexAttribArray(SHADER_COLOR_INDEX);

			glVertexAttribPointer(SHADER_VERTEX_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
			glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(Types::VertexData, VertexData::uv)));
			glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(Types::VertexData, VertexData::tid)));
			glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(Types::VertexData, VertexData::color)));

			GLuint* indices = NEW GLuint[RENDERER_INDICES_SIZE];

			for (unsigned int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
			{
				uint32 offset = (i / 6) * 4;

				indices[i + 0] = offset + 0;
				indices[i + 1] = offset + 1;
				indices[i + 2] = offset + 2;

				indices[i + 3] = offset + 2;
				indices[i + 4] = offset + 3;
				indices[i + 5] = offset + 0;
			}

			indexBuffer = NEW Graphics::IndexBuffer(indices, RENDERER_INDICES_SIZE);

			delete[] indices;
		}

		PhysicsRenderer2D::~PhysicsRenderer2D()
		{
			delete vertexArray;
			delete indexBuffer;
			glDeleteBuffers(1, &vertexBuffer);
		}

		void PhysicsRenderer2D::begin()
		{
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			buffer = (Types::VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		float PhysicsRenderer2D::submitTexture(Types::uint32 textureID)
		{
			if (!textureID)	DELTAENGINE_ERROR("[BatRend] Invalid texture ID!");

			float result = 0;
			bool found = false;
			for (Types::uint32 i = 0; i < textureSlots.size(); i++)
			{
				if (textureSlots[i] == textureID)
				{
					result = (float)(i + 1);
					found = true;
					break;
				}
			}

			if (!found)
			{
				if (textureSlots.size() >= RENDERER_MAX_TEXTURES)
				{
					DELTAENGINE_WARN("[BatRend] All the texture slots are in use! Flushing...");
					end();
					flush();
					begin();
				}

				textureSlots.push_back(textureID);
				result = (float)(textureSlots.size());
			}

			return result;
		}

		float PhysicsRenderer2D::submitTexture(const Graphics::Texture* texture)
		{
			return submitTexture(texture->getID());
		}

		void PhysicsRenderer2D::submit(const Graphics::Renderable2D* renderable, bool transformationStack)
		{
			const PhysicsRenderable2D* object = Utils::toPhysicsRenderable(renderable);

			const Types::uint32& color = object->getColor();
			const Maths::Vector2D& position = object->getPositionEx();
			const Maths::Vector2D& size = object->getSize();
			const std::vector<Maths::Vector2D>& uv = object->getUV();
			const GLuint tid = object->getTextureID();

			float ts = 0.0f;
			if (tid > 0) ts = submitTexture(object->getTexture());

			Maths::Matrix4 mat;

			if (transformationStack)
			{
				mat = *transformationStackTop;
			}
			else
			{
				mat = Maths::Matrix4(1.0f);
			}

			// TODO: Change mat4 rotation with sin/cos rotation (like OBBs)

			mat.translate(position.x, position.y, 0.0f);
			mat.rotate(object->getRotation(), 0.0f, 0.0f, 1.0f);

			const float hSizeX = size.x / 2;
			const float hSizeY = size.y / 2;

			buffer->vertex = mat * Maths::Vector2D(-hSizeX, -hSizeY);
			buffer->uv = uv[0];
			buffer->tid = ts;
			buffer->color = color;
			buffer++;

			buffer->vertex = mat * Maths::Vector2D(-hSizeX, hSizeY);
			buffer->uv = uv[1];
			buffer->tid = ts;
			buffer->color = color;
			buffer++;

			buffer->vertex = mat * Maths::Vector2D(hSizeX, hSizeY);
			buffer->uv = uv[2];
			buffer->tid = ts;
			buffer->color = color;
			buffer++;

			buffer->vertex = mat * Maths::Vector2D(hSizeX, -hSizeY);
			buffer->uv = uv[3];
			buffer->tid = ts;
			buffer->color = color;
			buffer++;

			indexCount += 6;
		}

		void PhysicsRenderer2D::end()
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void PhysicsRenderer2D::flush()
		{
			for (Types::uint32 i = 0; i < textureSlots.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, textureSlots[i]);
			}

			vertexArray->bind();
			indexBuffer->bind();

			glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, NULL);

			indexBuffer->unbind();
			vertexArray->unbind();

			indexCount = 0;
			textureSlots.clear();
		}

	}
}