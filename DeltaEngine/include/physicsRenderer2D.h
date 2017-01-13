#pragma once
#include "internal.h"
//#include "physicsRenderable2d.h"
#include "indexBuffer.h"
#include "vertexArray.h"
#include "types.h"
#include "font.h"
#include "framebuffer.h"
#include "matrix4.h"
#include "debug.h"
#include "utils.h"
#include "stack.h"

namespace DeltaEngine {
	namespace Physics {

		class PhysicsRenderable2D;

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

		class PhysicsRenderer2D
		{
		private:
			const Maths::Matrix4* transformationStackTop;
			Utils::Stack<Maths::Matrix4> transformationStack;

			Graphics::IndexBuffer* indexBuffer;
			Graphics::VertexArray* vertexArray;
			GLuint vertexBuffer;
			GLsizei indexCount;
			Types::VertexData* buffer;
			std::vector<GLuint> textureSlots;

			float submitTexture(Types::uint32 textureID);
			float submitTexture(const Graphics::Texture* texture);

			void init() { transformationStackTop = transformationStack.push(Maths::Matrix4::identity()); }

		public:
			DELTAENGINE_API PhysicsRenderer2D();
			DELTAENGINE_API ~PhysicsRenderer2D();

			inline void push(const Maths::Matrix4& matrix, bool override = false)
			{
				transformationStackTop = transformationStack.push(override ? matrix : transformationStack.top() * matrix);
			}

			inline void pop()
			{
				if (transformationStack.size() > 1)
				{
					transformationStackTop = transformationStack.pop();
				}
				else
				{
					//DELTAENGINE_ERROR("Attempted to pop the identity matrix from the transformation stack!");
					Debug::breakpoint();
				}
			}

			DELTAENGINE_API void begin();
			DELTAENGINE_API void submit(const PhysicsRenderable2D* renderable, bool transformationStack = false);
			DELTAENGINE_API void end();
			DELTAENGINE_API void flush();
		};

	}
}