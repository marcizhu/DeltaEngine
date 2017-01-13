#include "physicsRenderable2D.h"

namespace DeltaEngine {
	namespace Physics {

		void PhysicsRenderable2D::init(const Maths::Vector2D& pos, const Maths::Vector2D& size, Graphics::Texture* texture, float mass)
		{
			setUVDefaults();
			this->texture = texture;
			this->size = size;

			data = new float[7];

			// define body properties
			data[0] = b2_dynamicBody;
			data[1] = pos.x;
			data[2] = pos.y;
			data[3] = size.x;
			data[4] = size.y;
			data[5] = mass;
			data[6] = 0.0f; // friction
		}

	}
}