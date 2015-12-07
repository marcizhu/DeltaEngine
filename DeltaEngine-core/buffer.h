#pragma once

#ifndef __DELTAENGINE_BUFFER__
#define __DELTAENGINE_BUFFER__

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
			DELTAENGINE_API Buffer(GLfloat* data, GLsizei count, GLuint componentCount);

			DELTAENGINE_API inline void bind() const { glBindBuffer(GL_ARRAY_BUFFER, bufferID); };
			DELTAENGINE_API inline void unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); };

			DELTAENGINE_API inline GLuint getComponentCount() const { return componentCount; }
		};
			
	}
}

#endif