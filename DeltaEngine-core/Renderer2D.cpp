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
				
				if (renderable->hasMultiplePositions() == false)
				{
					renderable->getShader().setUniformMat4("ml_matrix", Maths::Matrix4::translate(renderable->getPosition()));
					glDrawElements(GL_TRIANGLES, renderable->getIndexBuffer()->getCount(), GL_UNSIGNED_SHORT, nullptr);
				} else
				{
					for (Maths::Vector3D t_pos : renderable->getMultiplePositions())
					{
						renderable->getShader().setUniformMat4("ml_matrix", Maths::Matrix4::translate(t_pos));
						glDrawElements(GL_TRIANGLES, renderable->getIndexBuffer()->getCount(), GL_UNSIGNED_SHORT, nullptr);
					}
				}
				
				renderable->getIndexBuffer()->unbind();
				renderable->getVertexArray()->unbind();
				
				renderQueue.pop_front();
			}
		}

	}
}
