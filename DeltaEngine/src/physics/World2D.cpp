#include "world2d.h"
#include "types.h"

using namespace DeltaEngine::Types;

namespace DeltaEngine {
	namespace Physics {

		Graphics::Renderable2D* World2D::add(Graphics::Renderable2D* object)
		{
			Physics::PhysicsRenderable2D* obj = object->toPhysicsRenderable();

			renderables.push_back(object);
			obj->applyForce(gravity * obj->getMass(), -90.0f); //TODO: -90.0f depends on the pr matrix!

			return object;
		}

		void World2D::update(float timestep)
		{
			for (Graphics::Renderable2D* renderable : renderables)
			{
				PhysicsRenderable2D* object = renderable->toPhysicsRenderable();

				if (!object->needsUpdate()) continue;
				if (limits && !area.contains(object->getPosition())) continue;

				byte itr = object->getIterations();

				float dt = (float)timestep / itr;

				for (byte i = 0; i < itr; i++)
				{
					object->update(dt);
				}
			}
		}

	}
}