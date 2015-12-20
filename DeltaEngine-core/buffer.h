#pragma once

#include <GLEW\glew.h>

#include "DeltaEngine.h"

namespace DeltaEngine {
	namespace Graphics {
		
		class Buffer
		{
		private:
			GLuint bufferID;
			GLuint componentCount;

		public:
			DELTAENGINE_API Buffer::Buffer(void* data, GLsizei size, GLuint componentCount);
			DELTAENGINE_API Buffer::~Buffer() { glDeleteBuffers(1, &bufferID); }

			DELTAENGINE_API inline void bind() const { glBindBuffer(GL_ARRAY_BUFFER, bufferID); };
			DELTAENGINE_API inline void unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); };

			DELTAENGINE_API inline GLuint getComponentCount() const { return componentCount; }
		};
			
	}
}