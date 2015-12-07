#pragma once

#ifndef __DELTAENGINE_VERTEX_ARRAY__
#define __DELTAENGINE_VERTEX_ARRAY__

#include <vector>
#include <GLEW\glew.h>

#include "DeltaEngine.h"
#include "buffer.h"

namespace DeltaEngine {
	namespace Graphics {
		
		class VertexArray
		{
		private:
			GLuint arrayID;
			std::vector<Buffer*> buffers;

		public:
			DELTAENGINE_API VertexArray() { glGenVertexArrays(1, &arrayID); };
			DELTAENGINE_API ~VertexArray();

			DELTAENGINE_API void addBuffer(Buffer* buffer, GLuint index);
			DELTAENGINE_API inline void bind() const { glBindVertexArray(arrayID); };
			DELTAENGINE_API inline void unbind() const { glBindVertexArray(0); };
		};
		
			
	}
}

#endif