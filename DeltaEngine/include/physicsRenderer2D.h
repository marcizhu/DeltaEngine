#pragma once
#include "internal.h"
#include "physicsRenderable2d.h"
#include "renderer2d.h"
#include "indexBuffer.h"
#include "vertexArray.h"
#include "types.h"
#include "font.h"
#include "framebuffer.h"

namespace DeltaEngine {
	namespace Physics {

#define RENDERER_MAX_SPRITES	60000
#define RENDERER_VERTEX_SIZE	sizeof(Types::VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6
#define RENDERER_MAX_TEXTURES	32

		// TODO: This depends on the shader! Let the user change this or autodetect
#define SHADER_VERTEX_INDEX 0
#define SHADER_UV_INDEX		1
#define SHADER_TID_INDEX	2
#define SHADER_COLOR_INDEX	3

		class PhysicsRenderer2D : public Graphics::Renderer2D
		{
		private:
			Graphics::IndexBuffer* indexBuffer;
			Graphics::VertexArray* vertexArray;
			GLuint vertexBuffer;
			GLsizei indexCount;
			Types::VertexData* buffer;
			std::vector<GLuint> textureSlots;

			float submitTexture(Types::uint32 textureID);
			float submitTexture(const Graphics::Texture* texture);

		public:
			DELTAENGINE_API PhysicsRenderer2D();
			DELTAENGINE_API ~PhysicsRenderer2D();

			DELTAENGINE_API void begin() override;
			DELTAENGINE_API void submit(const Graphics::Renderable2D* renderable, bool transformationStack = false) override;
			DELTAENGINE_API void end() override;
			DELTAENGINE_API void flush() override;
		};

	}
}