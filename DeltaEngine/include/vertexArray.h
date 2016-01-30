#pragma once

#include <vector>
#include <GLEW\glew.h>

#include "internal.h"
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

			DELTAENGINE_API void addBuffer(Buffer* buffer, GLuint index, GLenum type = GL_FLOAT);
			DELTAENGINE_API inline void bind() const { glBindVertexArray(arrayID); };
			DELTAENGINE_API inline void unbind() const { glBindVertexArray(0); };
		};
		
	}
}