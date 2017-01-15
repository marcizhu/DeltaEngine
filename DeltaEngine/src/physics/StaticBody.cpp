#include "StaticBody.h"

namespace DeltaEngine {
	namespace Physics {

		void StaticBody::createBody()
		{
			b2BodyDef bodyDef;
			bodyDef.type = b2_staticBody;
			bodyDef.position.Set(position.x, position.y);
			bodyDef.fixedRotation = false;

			body = world->CreateBody(&bodyDef);

			b2PolygonShape dynamicBox;
			dynamicBox.SetAsBox(size.x / 2.0f, size.y / 2.0f);

			b2FixtureDef fixtureDef;
			fixtureDef.shape = &dynamicBox;
			fixtureDef.friction = 0.0f;

			body->CreateFixture(&fixtureDef);
		}

	}
}