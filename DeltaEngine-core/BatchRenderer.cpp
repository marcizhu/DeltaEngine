#include "batchRenderer2d.h"
#include "types.h"

namespace DeltaEngine {
	namespace Graphics {

		// FIXME: Optimize this using vertexArrays, Buffers and IndexBuffers

		BatchRenderer2D::BatchRenderer2D() : Renderer2D(), indexCount(0)
		{
			glGenVertexArrays(1, &vertexArray);
			glGenBuffers(1, &vertexBuffer);

			glBindVertexArray(vertexArray);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_UV_INDEX);
			glEnableVertexAttribArray(SHADER_TID_INDEX);
			glEnableVertexAttribArray(SHADER_COLOR_INDEX);

			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
			glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::uv)));
			glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::tid)));
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

			FTAtlas = ftgl::texture_atlas_new(512, 512, 2);
			FTFont = ftgl::texture_font_new_from_file(FTAtlas, 32, "SourceSansPro-Light.ttf");
		}

		BatchRenderer2D::~BatchRenderer2D()
		{
			delete indexBuffer;
			glDeleteBuffers(1, &vertexBuffer);
			glDeleteVertexArrays(1, &vertexArray);
		}

		void BatchRenderer2D::begin()
		{
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			buffer = (Types::VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void BatchRenderer2D::submit(const Renderable2D* renderable)
		{
			Types::uint32 color = 0;
			Maths::Vector2D position = renderable->getPosition();
			const Maths::Vector2D& size = renderable->getSize();
			const std::vector<Maths::Vector2D>& uv = renderable->getUV();
			const GLuint tid = renderable->getTextureID();

			float ts = 0.0f;
			if (tid > 0)
			{
				bool found = false;
				for (uint32 i = 0; i < textureSlots.size(); i++)
				{
					if (textureSlots[i] == tid)
					{
						ts = (float)(i + 1);
						found = true;
						break;
					}
				}

				if (!found)
				{
					if (textureSlots.size() >= 32)
					{
						end();
						flush();
						begin();
					}
					textureSlots.push_back(tid);
					ts = (float)(textureSlots.size());
				}
			}
			else
			{
				color = renderable->getColor().getABGRColor();
			}

			buffer->vertex = position;
			buffer->uv = uv[0];
			buffer->tid = ts;
			buffer->color = color;
			buffer++;
			
			position.y += size.y;

			buffer->vertex = position;
			buffer->uv = uv[1];
			buffer->tid = ts;
			buffer->color = color;
			buffer++;

			position.x += size.x;
			
			buffer->vertex = position;
			buffer->uv = uv[2];
			buffer->tid = ts;
			buffer->color = color;
			buffer++;
			
			position.y -= size.y;

			buffer->vertex = position;
			buffer->uv = uv[3];
			buffer->tid = ts;
			buffer->color = color;
			buffer++;

			indexCount += 6;
		}

		void BatchRenderer2D::drawLine(const Maths::Vector2D& start, const Maths::Vector2D& end, unsigned int color)
		{
			double angle = atan2(start.y - end.y, start.x - end.x) + (PI / 2.0f);
			float x = (float)cos(angle);
			float y = (float)sin(angle);

			const float lineThinkness = 16.0f / 960.0f;

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
			
			buffer->vertex = end + Maths::Vector2D(x * lineThinkness, y * lineThinkness);
			buffer->uv = Maths::Vector2D(1, 0);
			buffer->tid = 0;
			buffer->color = color;
			buffer++;
			
			buffer->vertex = start + Maths::Vector2D(x * lineThinkness, y * lineThinkness);
			buffer->uv = Maths::Vector2D(1, 1);
			buffer->tid = 0;
			buffer->color = color;
			buffer++;

			indexCount += 6;
		}

		void BatchRenderer2D::drawString(const std::string& text, const Maths::Vector2D& position, const Types::Color& color)
		{
			//using namespace ftgl;
			
			/*int r = color.x * 255.0f;
			int g = color.y * 255.0f;
			int b = color.z * 255.0f;
			int a = color.w * 255.0f;*/
			
			unsigned int col = color.getABGRColor();
			
			float ts = 0.0f;
			bool found = false;
			for (int i = 0; i < textureSlots.size(); i++)
			{
				if (textureSlots[i] == FTAtlas->id)
				{
					ts = (float)(i + 1);
					found = true;
					break;
				}
			}
			
			if (!found)
			{
				if (textureSlots.size() >= 32)
				{
					end();
					flush();
					begin();
				}

				textureSlots.push_back(FTAtlas->id);
				ts = (float)(textureSlots.size());
			}
			
			float scaleX = 960.0f / 32.0f;
			float scaleY = 540.0f / 18.0f;
			
			float x = position.x;
			
			for (int i = 0; i < text.length(); i++)
			{
				char c = text[i];
				texture_glyph_t* glyph = texture_font_get_glyph(FTFont, &c);
				if (glyph != NULL)
				{
					
					if (i > 0)
					{
						float kerning = texture_glyph_get_kerning(glyph, &text[i - 1]);
						x += kerning / scaleX;
					}
					
					float x0 = x + glyph->offset_x / scaleX;
					float y0 = position.y + glyph->offset_y / scaleY;
					float x1 = x0 + glyph->width / scaleX;
					float y1 = y0 - glyph->height / scaleY;
					
					float u0 = glyph->s0;
					float v0 = glyph->t0;
					float u1 = glyph->s1;
					float v1 = glyph->t1;
					
					buffer->vertex = Maths::Vector2D(x0, y0);
					buffer->uv = Maths::Vector2D(u0, v0);
					buffer->tid = ts;
					buffer->color = col;
					buffer++;
					
					buffer->vertex = Maths::Vector2D(x0, y1);
					buffer->uv = Maths::Vector2D(u0, v1);
					buffer->tid = ts;
					buffer->color = col;
					buffer++;
					
					buffer->vertex = Maths::Vector2D(x1, y1);
					buffer->uv = Maths::Vector2D(u1, v1);
					buffer->tid = ts;
					buffer->color = col;
					buffer++;
					
					buffer->vertex = Maths::Vector2D(x1, y0);
					buffer->uv = Maths::Vector2D(u1, v0);
					buffer->tid = ts;
					buffer->color = col;
					buffer++;
					
					indexCount += 6;
					
					x += glyph->advance_x / scaleX;
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
			for (uint32 i = 0; i < textureSlots.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, textureSlots[i]);
			}

			glBindVertexArray(vertexArray);
			indexBuffer->bind();

			glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, NULL);

			indexBuffer->unbind();
			glBindVertexArray(0);

			indexCount = 0;
		}

	}
}
