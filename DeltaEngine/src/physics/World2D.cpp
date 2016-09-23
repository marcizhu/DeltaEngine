#include "world2d.h"
#include "types.h"
#include "utils.h"

using namespace DeltaEngine::Types;

namespace DeltaEngine {
	namespace Physics {

		Graphics::Renderable2D* World2D::add(Graphics::Renderable2D* object)
		{
			Physics::PhysicsRenderable2D* obj = Utils::toPhysicsRenderable(object);

			renderables.push_back(object);

			obj->applyForce(gravity * obj->getMass(), this->projectionMatrix.getDownDirection() * 90.0f);

			return object;
		}

		void World2D::update(float timestep)
		{
			for (Graphics::Renderable2D* renderable : renderables)
			{
				PhysicsRenderable2D* object = Utils::toPhysicsRenderable(renderable);

				if (!object->needsUpdate()) continue;
				if (limits && !area.contains(object->getPosition())) continue;

				Types::byte itr = object->getIterations();

				float dt = (float)timestep / itr;

				for (Types::byte i = 0; i < itr; i++)
				{
					object->update(dt);
				}
			}
		}

	}
}