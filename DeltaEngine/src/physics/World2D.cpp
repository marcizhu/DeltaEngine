#include <Box2D\Box2D.h>

#include "world2d.h"
#include "types.h"
#include "utils.h"

namespace DeltaEngine {
	namespace Physics {

		World2D::World2D(Graphics::Renderer2D* renderer, Graphics::Shader* shader, const Maths::Matrix4& projectionMatrix, const Maths::Vector2D& gravity)
			: Layer2D(renderer, shader, projectionMatrix), gravity(gravity)
		{
			b2Vec2 grav(gravity.x, gravity.y);
			world = new b2World(grav);
		}

		Graphics::Renderable2D* World2D::add(Graphics::Renderable2D* object)
		{
			Physics::PhysicsRenderable2D* obj = Utils::toPhysicsRenderable(object);

			renderables.push_back(object);

			const float* data = obj->getData();

			b2BodyDef bodyDef;
			bodyDef.type = b2_dynamicBody;
			bodyDef.position.Set(data[1], data[2]);
			obj->setBody(world->CreateBody(&bodyDef));

			b2PolygonShape dynamicBox;
			dynamicBox.SetAsBox(data[3], data[4]);

			b2FixtureDef fixtureDef;
			fixtureDef.shape = &dynamicBox;
			fixtureDef.density = data[5];
			fixtureDef.friction = data[6]; // TODO: Add friction

			obj->getBody()->CreateFixture(&fixtureDef);

			return object;
		}

		void World2D::step(float timestep, int vIterations, int posIterations)
		{
			world->Step(timestep, vIterations, posIterations);
		}

	}
}