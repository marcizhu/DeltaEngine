#pragma once

#ifndef __DELTAENGINE_BATCH_RENDERER__
#define __DELTAENGINE_BATCH_RENDERER__

#include "DeltaEngine.h"
#include "renderable2d.h"
#include "renderer2d.h"
#include "indexBuffer.h"
#include "types.h"
#include "font.h"

namespace DeltaEngine {
	namespace Graphics {
		
#define RENDERER_MAX_SPRITES	60000
#define RENDERER_VERTEX_SIZE	sizeof(Types::VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6
#define RENDERER_MAX_TEXTURES	32

#define SHADER_VERTEX_INDEX 0
#define SHADER_UV_INDEX		1
#define SHADER_TID_INDEX	2
#define SHADER_COLOR_INDEX	3


		class BatchRenderer2D : public Renderer2D
		{
		private:
			GLuint vertexArray;
			GLuint vertexBuffer;
			IndexBuffer* indexBuffer;
			GLsizei indexCount;
			Types::VertexData* buffer;
			std::vector<GLuint> textureSlots;

			float BatchRenderer2D::submitTexture(Types::uint32 textureID);
			float BatchRenderer2D::submitTexture(const Texture* texture);

		public:
			DELTAENGINE_API BatchRenderer2D();
			DELTAENGINE_API ~BatchRenderer2D();

			DELTAENGINE_API void begin() override;
			DELTAENGINE_API void submit(const Renderable2D* renderable) override;
			DELTAENGINE_API void end() override;
			DELTAENGINE_API void flush() override;

			DELTAENGINE_API void drawString(const std::string& text, const Maths::Vector2D& position, const Font& font, const Types::uint32 color) override;

			DELTAENGINE_API void drawLine(const Maths::Vector2D& start, const Maths::Vector2D& end, unsigned int color) override;
		};
	}
}

#endif