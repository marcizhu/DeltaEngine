#pragma once

#ifndef __DELTAENGINE_INDEX_BUFFER__
#define __DELTAENGINE_INDEX_BUFFER__

#include <GLEW\glew.h>

#include "DeltaEngine.h"

namespace DeltaEngine {
	namespace Graphics {
		
		class IndexBuffer
		{
		private:
			GLuint bufferID;
			GLuint count;

		public:
			DELTAENGINE_API IndexBuffer(GLushort* data, GLsizei count);

			DELTAENGINE_API inline void bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID); };
			DELTAENGINE_API inline void unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); };

			DELTAENGINE_API inline GLuint getCount() const { return count; }
		};
	}
}


#endif