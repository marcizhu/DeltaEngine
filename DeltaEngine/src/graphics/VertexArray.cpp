#include "vertexarray.h"
#include "types.h"
#include "memoryManager.h"

using namespace DeltaEngine::Types;

namespace DeltaEngine {
	namespace Graphics {

		VertexArray::~VertexArray()
		{
			for (uint32 i = 0; i < buffers.size(); i++)
				DELETE buffers[i];

			glDeleteVertexArrays(1, &arrayID);
		}

		void VertexArray::addBuffer(Buffer* buffer, GLuint index, GLenum type)
		{
			bind();
			buffer->bind();

			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, buffer->getComponentCount(), type, GL_FALSE, 0, 0);

			buffer->unbind();
			unbind();

			buffers.push_back(buffer);
		}

	}
}
