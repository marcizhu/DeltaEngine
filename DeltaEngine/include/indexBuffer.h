#pragma once

#include <GLEW\glew.h>

#include "internal.h"

namespace DeltaEngine {
	namespace Graphics {

		class IndexBuffer
		{
		private:
			GLuint bufferID;
			GLuint count;

		public:
			DELTAENGINE_API IndexBuffer(GLushort* data, GLsizei count);
			DELTAENGINE_API IndexBuffer(GLuint* data, GLsizei count);
			DELTAENGINE_API IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &bufferID); }

			DELTAENGINE_API inline void bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID); };
			DELTAENGINE_API inline void unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); };

			DELTAENGINE_API inline GLuint getCount() const { return count; }
		};
	}
}