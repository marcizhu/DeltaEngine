#include <deque>

#include "simpleRenderer2d.h"
#include "types.h"

using namespace DeltaEngine::Types;

namespace DeltaEngine {
	namespace Graphics {

		void SimpleRenderer2D::flush()
		{
			while (!renderQueue.empty())
			{
				const SimpleRenderable2D* renderable = renderQueue.front();
				renderable->getVertexArray()->bind();
				renderable->getIndexBuffer()->bind();

				Maths::Matrix4 matrix = Maths::Matrix4(1.0f);
				matrix.translate(renderable->getPosition().x, renderable->getPosition().y, 0);

				renderable->getShader().setUniformMat4("ml_matrix", matrix);
				glDrawElements(GL_TRIANGLES, renderable->getIndexBuffer()->getCount(), GL_UNSIGNED_SHORT, nullptr);
				
				renderable->getIndexBuffer()->unbind();
				renderable->getVertexArray()->unbind();
				
				renderQueue.pop_front();
			}
		}

	}
}
