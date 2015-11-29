#include <deque>

#include "renderer2d.h"

namespace DeltaEngine {
	namespace Graphics {

		void Renderer2D::flush()
		{
			while (!renderQueue.empty())
			{
				const Renderable2D* renderable = renderQueue.front();
				renderable->getVertexArray()->bind();
				renderable->getIndexBuffer()->bind();

				for (Maths::Vector2D t_pos : renderable->getPositions())
				{
					renderable->getShader().setUniformMat4("ml_matrix", Maths::Matrix4::translate(Maths::Vector3D(t_pos.x, t_pos.y, 0)));
					glDrawElements(GL_TRIANGLES, renderable->getIndexBuffer()->getCount(), GL_UNSIGNED_SHORT, nullptr);
				}
				
				renderable->getIndexBuffer()->unbind();
				renderable->getVertexArray()->unbind();
				
				renderQueue.pop_front();
			}
		}

		void Renderer2D::sort()
		{
			int index = 0;

			std::deque<const Renderable2D*> temp;
			while (!renderQueue.empty())
			{
				for (int i = 0; i < renderQueue.size(); i++)
				{
					if (renderQueue[i]->getZorder() == index)
					{
						temp.push_back(renderQueue[i]);
						renderQueue.erase(renderQueue.begin() + i);
					}
				}

				index++;
			}

			renderQueue = temp;
		}

	}
}
