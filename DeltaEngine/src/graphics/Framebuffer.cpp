#include "framebuffer.h"
#include "memoryManager.h"

namespace DeltaEngine {
	namespace Graphics {

		Framebuffer::Framebuffer(Types::uint32 width, Types::uint32 height)
			: width(width), height(height)
		{
			glGenFramebuffers(1, &data.framebufferID);
			glGenRenderbuffers(1, &data.depthbufferID);

			texture = NEW Texture(width, height, 32);

			glBindRenderbuffer(GL_RENDERBUFFER, data.depthbufferID);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);

			glBindFramebuffer(GL_FRAMEBUFFER, data.framebufferID);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture->getID(), 0);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, data.depthbufferID);
		}

		Framebuffer::~Framebuffer()
		{
			delete texture;

			glDeleteFramebuffers(1, &data.framebufferID);
			glDeleteRenderbuffers(1, &data.depthbufferID);
		}

		void Framebuffer::bind() const
		{
			glBindFramebuffer(GL_FRAMEBUFFER, data.framebufferID);
			glViewport(0, 0, width, height);
		}

		void Framebuffer::unbind() const
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void Framebuffer::clear() const
		{
			glClearColor(clearColor.A / 255.0f, clearColor.B / 255.0f, clearColor.G / 255.0f, clearColor.R / 255.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

	}
}