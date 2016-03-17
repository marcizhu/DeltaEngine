#include "batchRenderer2d.h"
#include "types.h"
#include "maths.h"
#include "log.h"
#include "memoryManager.h"

namespace DeltaEngine {
	namespace Graphics {

		// FIXME: Optimize this using Buffers
		// TODO: Rewrite Buffer.cpp

		BatchRenderer2D::BatchRenderer2D() : Renderer2D(), indexCount(0)
		{
			vertexArray = NEW VertexArray();
			glGenBuffers(1, &vertexBuffer);

			vertexArray->bind();
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_UV_INDEX);
			glEnableVertexAttribArray(SHADER_TID_INDEX);
			glEnableVertexAttribArray(SHADER_COLOR_INDEX);

			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
			glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(Types::VertexData, VertexData::uv)));
			glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(Types::VertexData, VertexData::tid)));
			glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(Types::VertexData, VertexData::color)));

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			GLuint* indices = NEW GLuint[RENDERER_INDICES_SIZE];

			for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
			{
				uint32 offset = (i / 6) * 4;

				indices[i + 0] = offset + 0;
				indices[i + 1] = offset + 1;
				indices[i + 2] = offset + 2;

				indices[i + 3] = offset + 2;
				indices[i + 4] = offset + 3;
				indices[i + 5] = offset + 0;
			}

			indexBuffer = NEW IndexBuffer(indices, RENDERER_INDICES_SIZE);

			DELETE indices;

			glBindVertexArray(0);
		}

		BatchRenderer2D::~BatchRenderer2D()
		{
			DELETE vertexArray;
			DELETE indexBuffer;
			glDeleteBuffers(1, &vertexBuffer);
		}

		void BatchRenderer2D::begin()
		{
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			buffer = (Types::VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		float BatchRenderer2D::submitTexture(Types::uint32 textureID)
		{
			if (!textureID)	DELTAENGINE_ERROR("[BatRend] Invalid texture ID!");

			float result = 0.0f;
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
					end();
					flush();
					begin();
				}

				textureSlots.push_back(textureID);
				result = (float)(textureSlots.size());
			}

			return result;
		}

		float BatchRenderer2D::submitTexture(const Texture* texture)
		{
			return submitTexture(texture->getID());
		}

		void BatchRenderer2D::submit(const Renderable2D* renderable)
		{
			const Types::uint32& color = renderable->getColor();
			const Maths::Vector2D& position = renderable->getPosition();
			const Maths::Vector2D& size = renderable->getSize();
			const std::vector<Maths::Vector2D>& uv = renderable->getUV();
			const GLuint tid = renderable->getTextureID();

			float ts = 0.0f;
			if (tid > 0) ts = submitTexture(renderable->getTexture());

			buffer->vertex = position;
			buffer->uv = uv[0];
			buffer->tid = ts;
			buffer->color = color;
			buffer++;

			buffer->vertex = Maths::Vector2D(position.x, position.y + size.y);
			buffer->uv = uv[1];
			buffer->tid = ts;
			buffer->color = color;
			buffer++;

			buffer->vertex = Maths::Vector2D(position.x + size.x, position.y + size.y);
			buffer->uv = uv[2];
			buffer->tid = ts;
			buffer->color = color;
			buffer++;

			buffer->vertex = Maths::Vector2D(position.x + size.x, position.y);
			buffer->uv = uv[3];
			buffer->tid = ts;
			buffer->color = color;
			buffer++;

			indexCount += 6;
		}

		void BatchRenderer2D::drawLine(const Maths::Vector2D& start, const Maths::Vector2D& end, float thickness, unsigned int color)
		{
			double angle = atan2(start.y - end.y, start.x - end.x) + (PI / 2.0f);
			float x = (float)cos(angle);
			float y = (float)sin(angle);

			buffer->vertex = start;
			buffer->uv = Maths::Vector2D(0, 1);
			buffer->tid = 0;
			buffer->color = color;
			buffer++;

			buffer->vertex = end;
			buffer->uv = Maths::Vector2D(0, 0);
			buffer->tid = 0;
			buffer->color = color;
			buffer++;

			buffer->vertex = end + Maths::Vector2D(x * thickness, y * thickness);
			buffer->uv = Maths::Vector2D(1, 0);
			buffer->tid = 0;
			buffer->color = color;
			buffer++;

			buffer->vertex = start + Maths::Vector2D(x * thickness, y * thickness);
			buffer->uv = Maths::Vector2D(1, 1);
			buffer->tid = 0;
			buffer->color = color;
			buffer++;

			indexCount += 6;
		}

		void BatchRenderer2D::drawString(const std::string& text, const Maths::Vector2D& position, const Font& font, const Types::uint32 color)
		{
			float ts = 0.0f;
			ts = submitTexture(font.getID());

			const Maths::Vector2D& scale = font.getScale();

			float x = position.x;
			float y = position.y;

			texture_font_t* ftFont = font.getFTFont();

			for (Types::uint32 i = 0; i < text.length(); i++)
			{
				char c = text[i];
				texture_glyph_t* glyph = texture_font_get_glyph(ftFont, &c);

				if (glyph)
				{
					if (i > 0)
					{
						float kerning = texture_glyph_get_kerning(glyph, &text[i - 1]);
						x += kerning / scale.x;
					}

					if (c == '\n')
					{
						// vertical space = (x + 6) / 3
						y -= (glyph->advance_y > 0.0f ? glyph->advance_y : (glyph->height + (font.getSize() + 6) / 3)) / scale.y;
						x = position.x;
						continue;
					}

					float x0 = x + glyph->offset_x / scale.x;
					float y0 = y + glyph->offset_y / scale.y;
					float x1 = x0 + glyph->width / scale.x;
					float y1 = y0 - glyph->height / scale.y;

					float u0 = glyph->s0;
					float v0 = glyph->t0;
					float u1 = glyph->s1;
					float v1 = glyph->t1;

					buffer->vertex = Maths::Vector2D(x0, y0);
					buffer->uv = Maths::Vector2D(u0, v0);
					buffer->tid = ts;
					buffer->color = color;
					buffer++;

					buffer->vertex = Maths::Vector2D(x0, y1);
					buffer->uv = Maths::Vector2D(u0, v1);
					buffer->tid = ts;
					buffer->color = color;
					buffer++;

					buffer->vertex = Maths::Vector2D(x1, y1);
					buffer->uv = Maths::Vector2D(u1, v1);
					buffer->tid = ts;
					buffer->color = color;
					buffer++;

					buffer->vertex = Maths::Vector2D(x1, y0);
					buffer->uv = Maths::Vector2D(u1, v0);
					buffer->tid = ts;
					buffer->color = color;
					buffer++;

					indexCount += 6;

					x += glyph->advance_x / scale.x;
				}
			}
		}

		void BatchRenderer2D::end()
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void BatchRenderer2D::flush()
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