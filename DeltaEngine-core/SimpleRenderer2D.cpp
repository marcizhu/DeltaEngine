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
				const Renderable2D* renderable = renderQueue.front();
				renderable->getVertexArray()->bind();
				renderable->getIndexBuffer()->bind();

				for (Maths::Vector2D t_pos : renderable->getPositions())
				{
					Maths::Matrix4 matrix = Maths::Matrix4(1.0f);
					matrix.translate(Maths::Vector3D(t_pos.x, t_pos.y, 0));
					//if(t_pos.x == 1.0f && t_pos.y == 1.0f) matrix.rotate(45.0f, Maths::Vector3D(0, 0, 1));

					renderable->getShader().setUniformMat4("ml_matrix", matrix);
					glDrawElements(GL_TRIANGLES, renderable->getIndexBuffer()->getCount(), GL_UNSIGNED_SHORT, nullptr);
				}
				
				renderable->getIndexBuffer()->unbind();
				renderable->getVertexArray()->unbind();
				
				renderQueue.pop_front();
			}
		}

		void SimpleRenderer2D::sort()
		{
			uint32 index = 0, i = 0;
			std::deque<const Renderable2D*> temp;

			while (!renderQueue.empty())
			{
				if (renderQueue[i]->getZorder() == index)
				{
					temp.push_back(renderQueue[i]);
					renderQueue.erase(renderQueue.begin() + i);
				} 
				else i++;

				if (i >= renderQueue.size())
				{
					i = 0;
					index++;
				}
			}

			renderQueue = temp;
		}

	}
}
