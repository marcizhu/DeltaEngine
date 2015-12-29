#include "layer2d.h"
#include "matrix4.h"

namespace DeltaEngine {
	namespace Graphics {

		Layer2D::Layer2D(Renderer2D* renderer, Shader* shader, const Maths::Matrix4& projectionMatrix)
			: renderer(renderer), shader(shader), projectionMatrix(projectionMatrix)
		{
			viewMatrix = Maths::Matrix4::identity();
			
			shader->enable();
			shader->setUniformMat4("pr_matrix", projectionMatrix);
			shader->setUniformMat4("vw_matrix", viewMatrix);
			shader->disable();
		}

		Layer2D::~Layer2D()
		{
			delete shader;
			delete renderer;

			for (int i = 0; i < renderables.size(); i++)
				delete renderables[i];
		}

		void Layer2D::render()
		{
			shader->enable();
			renderer->begin();

			for (const Renderable2D* renderable : renderables)
				renderer->submit(renderable);
			
			renderer->end();
			renderer->flush();
		}

		void Layer2D::setCameraPosition(float x, float y)
		{
			xCamera = x;
			yCamera = y;

			viewMatrix.translate(x, y, 0.0f);

			shader->enable();
			shader->setUniformMat4("vw_matrix", viewMatrix);
			shader->disable();
		}

	}
}