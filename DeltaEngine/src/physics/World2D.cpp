#include <Box2D\Box2D.h>

#include "world2d.h"
#include "types.h"
#include "utils.h"
#include "physicsRenderer2d.h"

namespace DeltaEngine {
	namespace Physics {

		World2D::World2D(Graphics::Shader* shader, Maths::Matrix4 pr_matrix, const Maths::Vector2D& gravity)
			: renderer(new PhysicsRenderer2D()), shader(shader), projectionMatrix(pr_matrix), gravity(gravity)
		{
			viewMatrix = Maths::Matrix4::identity();

			shader->enable();
			shader->setUniformMat4("pr_matrix", projectionMatrix);
			shader->setUniformMat4("vw_matrix", viewMatrix);
			shader->disable();

			b2Vec2 grav(gravity.x, gravity.y);
			world = new b2World(grav);
		}

		World2D::~World2D()
		{
			delete shader;
			delete renderer;
			delete world;

			for (Types::uint32 i = 0; i < renderables.size(); i++)
				delete renderables[i];
		}

		PhysicsRenderable2D* World2D::add(PhysicsRenderable2D* object)
		{
			renderables.push_back(object);

			object->setWorld(this->world);

			return object;
		}

		void World2D::step(float timestep, int vIterations, int posIterations) { world->Step(timestep, vIterations, posIterations); }

		void World2D::render()
		{
			shader->enable();
			renderer->begin();

			for (const PhysicsRenderable2D* renderable : renderables)
				renderable->submit(renderer);

			renderer->end();
			renderer->flush();
		}

		//TODO: let the user change the uniform name
		void World2D::setViewMatrix()
		{
			shader->enable();
			shader->setUniformMat4("vw_matrix", viewMatrix);
			shader->disable();
		}

		void World2D::setCameraPosition(float x, float y)
		{
			xCamera = x;
			yCamera = y;

			viewMatrix.translate(x, y, 0.0f);

			setViewMatrix();
		}

		void World2D::rotate(float angle, Maths::Vector3D axis)
		{
			viewMatrix.rotate(angle, axis);

			setViewMatrix();
		}

		void World2D::rotate(float angle, float xAxis, float yAxis, float zAxis)
		{
			viewMatrix.rotate(angle, xAxis, yAxis, zAxis);

			setViewMatrix();
		};

		void World2D::remove(PhysicsRenderable2D* renderable)
		{
			const auto& it = std::find(renderables.begin(), renderables.end(), renderable);

			if (it != renderables.end()) renderables.erase(it);
		}

	}
}