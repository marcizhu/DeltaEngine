#pragma once

#ifndef __DELTAENGINE_BATCH_RENDERER__
#define __DELTAENGINE_BATCH_RENDERER__

#include "DeltaEngine.h"
#include "renderer2d.h"
#include "indexBuffer.h"
#include "types.h"

namespace DeltaEngine {
	namespace Graphics {
		
#define RENDERER_MAX_SPRITES	60000
#define RENDERER_VERTEX_SIZE	sizeof(Types::VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX 0
#define SHADER_UV_INDEX		1
#define SHADER_COLOR_INDEX	2
			
		class BatchRenderer2D : public Renderer2D
		{
		private:
			GLuint vertexArray;
			GLuint vertexBuffer;
			IndexBuffer* indexBuffer;
			GLsizei indexCount;
			Types::VertexData* buffer;

		public:
			DELTAENGINE_API BatchRenderer2D();
			DELTAENGINE_API ~BatchRenderer2D();

			DELTAENGINE_API void begin() override;
			DELTAENGINE_API void submit(const Renderable2D* renderable) override;
			DELTAENGINE_API void end() override;
			DELTAENGINE_API void flush() override;
		};
	}
}

#endif