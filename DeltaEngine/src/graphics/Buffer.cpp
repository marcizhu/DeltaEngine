#include <GLEW\glew.h>

#include "buffer.h"

namespace DeltaEngine {
	namespace Graphics {

		Buffer::Buffer(GLfloat* data, GLsizei count, GLuint componentCount) : componentCount(componentCount)
		{
			glGenBuffers(1, &bufferID);
			glBindBuffer(GL_ARRAY_BUFFER, bufferID);
			glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

	}
}
