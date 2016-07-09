#pragma once

#include <GLEW\glew.h>

#include "internal.h"
#include "types.h"
#include "vector2d.h"
#include "texture.h"

namespace DeltaEngine {
	namespace Graphics {

		class Framebuffer
		{
		private:
			struct FramebufferData
			{
				GLuint framebufferID;
				GLuint depthbufferID;
			};

			Texture* texture;
			FramebufferData data;
			Types::uint32 width;
			Types::uint32 height;
			Types::Color clearColor;

		public:
			//DELTAENGINE_API Framebuffer(const Maths::Vector2D& size);
			DELTAENGINE_API Framebuffer(Types::uint32 width, Types::uint32 height);
			DELTAENGINE_API ~Framebuffer();

			DELTAENGINE_API void bind() const;
			DELTAENGINE_API void unbind() const;
			DELTAENGINE_API void clear() const;

			DELTAENGINE_API inline const Maths::Vector2D getSize() const { return Maths::Vector2D((float)width, (float)height); }
			DELTAENGINE_API inline const Types::uint32 getWidth() const { return width; }
			DELTAENGINE_API inline const Types::uint32 getHeight() const { return height; }
			DELTAENGINE_API inline const Texture* getTexture() const { return texture; }

			DELTAENGINE_API inline void setClearColor(const Types::Color& color) { clearColor = color; }
		};

	}
}