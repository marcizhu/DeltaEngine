#include "vertexarray.h"

namespace DeltaEngine {
	namespace Graphics {		
		
		VertexArray::~VertexArray()
		{
			for (int i = 0; i < buffers.size(); i)
				delete buffers[i];
		}
		
		void VertexArray::addBuffer(Buffer* buffer, GLuint index)
		{
			bind();
			buffer->bind();

			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);

			buffer->unbind();
			unbind();
		}
			
	}
}
