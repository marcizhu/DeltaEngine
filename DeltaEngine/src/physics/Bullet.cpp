#include "Bullet.h"

namespace DeltaEngine {
	namespace Physics {

		void Bullet::createBody()
		{
			b2BodyDef bodyDef;
			bodyDef.type = b2_dynamicBody;
			bodyDef.position.Set(position.x, position.y);
			bodyDef.bullet = true;

			body = world->CreateBody(&bodyDef);

			b2PolygonShape dynamicBox;
			dynamicBox.SetAsBox(size.x / 2.0f, size.y / 2.0f);

			b2FixtureDef fixtureDef;
			fixtureDef.shape = &dynamicBox;
			fixtureDef.density = mass;
			fixtureDef.friction = 0.0f;

			body->CreateFixture(&fixtureDef);
		}

	}
}