#include "indexbuffer.h"

namespace DeltaEngine {
	namespace Graphics {

		IndexBuffer::IndexBuffer(GLushort* data, GLsizei count) : count(count)
		{
			glGenBuffers(1, &bufferID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		IndexBuffer::IndexBuffer(GLuint* data, GLsizei count) : count(count)
		{
			glGenBuffers(1, &bufferID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

	}
}
