#include "physicsRenderable2D.h"

namespace DeltaEngine {
	namespace Physics {

		PhysicsRenderable2D::~PhysicsRenderable2D()
		{
			world->DestroyBody(body);
		}

	}
}