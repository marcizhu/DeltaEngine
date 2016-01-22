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

			for (uint32 i = 0; i < renderables.size(); i++)
				delete renderables[i];
		}

		void Layer2D::render()
		{
			shader->enable();
			renderer->begin();

			for (const Renderable2D* renderable : renderables)
				renderable->submit(renderer);
			
			//it works!
			//renderer->drawLine(Maths::Vector2D(0.0f, 0.0f), Maths::Vector2D(16.0f, 9.0f), 0xFF007FFF);

			renderer->end();
			renderer->flush();
		}

		void Layer2D::setViewMatrix()
		{
			shader->enable();
			shader->setUniformMat4("vw_matrix", viewMatrix);
			shader->disable();
		}

		//TODO: let the user change the uniform name
		void Layer2D::setCameraPosition(float x, float y)
		{
			xCamera = x;
			yCamera = y;

			viewMatrix.translate(x, y, 0.0f);

			setViewMatrix();
		}

		void Layer2D::rotate(float angle, Maths::Vector3D axis)
		{ 
			viewMatrix.rotate(angle, axis); 
		
			setViewMatrix();
		}

		void Layer2D::rotate(float angle, float xAxis, float yAxis, float zAxis) 
		{ 
			viewMatrix.rotate(angle, xAxis, yAxis, zAxis);

			setViewMatrix();
		};

	}
}