#include "layer2d.h"

namespace DeltaEngine {
	namespace Graphics {

		Layer2D::Layer2D(Renderer2D* renderer, Shader* shader, const Maths::Matrix4& projectionMatrix)
			: renderer(renderer), shader(shader), projectionMatrix(projectionMatrix)
		{
			shader->enable();
			shader->setUniformMat4("pr_matrix", projectionMatrix);
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

	}
}