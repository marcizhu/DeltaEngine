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

				/*for (Maths::Vector2D t_pos : renderable->getPosition())
				{
					Maths::Matrix4 matrix = Maths::Matrix4(1.0f);
					matrix.translate(t_pos.x, t_pos.y, 0);
					//if(t_pos.x == 1.0f && t_pos.y == 1.0f) matrix.rotate(45.0f, 0.0f, 0.0f, 1.0f);

					renderable->getShader().setUniformMat4("ml_matrix", matrix);
					glDrawElements(GL_TRIANGLES, renderable->getIndexBuffer()->getCount(), GL_UNSIGNED_SHORT, nullptr);
				}*/

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
