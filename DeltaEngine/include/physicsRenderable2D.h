#pragma once

#include "renderable2d.h"
#include "aabb.h"
#include "log.h"

//class DeltaEngine::Graphics::Renderable2D;

namespace DeltaEngine {
	namespace Physics {

		class PhysicsRenderable2D : public Graphics::Renderable2D
		{
		private:
			float rotationAngle; // in degrees!
			float mass;
			Types::byte iterations;
			Maths::Vector2D force; // in units per second every second (u / s^2)
			Maths::Vector2D velocity; // in units per second (u / s)
			Maths::AABB aabb;

		public:
			PhysicsRenderable2D(float x, float y, float width, float height, Types::Color color, float mass, Types::byte it)
				: Renderable2D(Maths::Vector2D(x, y), Maths::Vector2D(width, height), color), aabb(position, position + size), mass(mass), iterations(it)
			{ this->texture = nullptr; rotationAngle = 0.0f; force = velocity = Maths::Vector2D(0, 0); };

			PhysicsRenderable2D(float x, float y, float width, float height, Types::uint32 color, float mass, Types::byte it)
				: Renderable2D(Maths::Vector2D(x, y), Maths::Vector2D(width, height), color), aabb(position, position + size), mass(mass), iterations(it)
			{ this->texture = nullptr; rotationAngle = 0.0f; force = velocity = Maths::Vector2D(0, 0); };

			PhysicsRenderable2D(float x, float y, float width, float height, Graphics::Texture* texture, float mass, Types::byte it)
				: Renderable2D(Maths::Vector2D(x, y), Maths::Vector2D(width, height), 0xffffffff), aabb(position, position + size), mass(mass), iterations(it)
			{ this->texture = texture; rotationAngle = 0.0f; force = velocity = Maths::Vector2D(0, 0); }

			PhysicsRenderable2D(float x, float y, float width, float height, Graphics::Sprite sprite, float mass, Types::byte it)
				: Renderable2D(Maths::Vector2D(x, y), Maths::Vector2D(width, height), 0xffffffff), aabb(position, position + size), mass(mass), iterations(it)
			{ this->texture = nullptr; rotationAngle = 0.0f; force = velocity = Maths::Vector2D(0, 0); }

			void update(float dt)
			{
				velocity += (force / mass) * dt;

				// tunneling
				if(abs(velocity.x * dt) >= size.x) DELTAENGINE_WARN("[Physics] Horizontal speed is too fast! (", velocity.x,")");
				if(abs(velocity.y * dt) >= size.y) DELTAENGINE_WARN("[Physics] Vertical speed is too fast! (", velocity.y, ")");

				position += velocity * dt + ((force / mass) * dt * dt / 2.0f);

				aabb = Maths::AABB(position, position + size);
			}

			inline bool needsUpdate() { return force.distance() != 0.0f || velocity.distance() != 0.0f; }

			inline float getRotation() const { return rotationAngle; }
			inline Maths::Vector2D getAcceleration() const { return (force / mass); }
			inline Maths::Vector2D getVelocity() const { return velocity; }
			inline Types::byte getIterations() const { return iterations; }
			inline float getMass() const { return mass; }

			inline float getForce() const { return force.distance(); }

			inline void setRotation(float degrees) { rotationAngle = degrees; }

			inline void setAcceleration(float unitsPerSecond)
			{
				force.x = cos(Maths::toRadians(rotationAngle)) * unitsPerSecond * mass;
				force.y = sin(Maths::toRadians(rotationAngle)) * unitsPerSecond * mass;
			}

			inline void setAcceleration(float unitsPerSecond, float angle)
			{
				force.x = cos(Maths::toRadians(angle)) * unitsPerSecond * mass;
				force.y = sin(Maths::toRadians(angle)) * unitsPerSecond * mass;
			}

			inline void setVelocity(float unitsPerSecond)
			{
				velocity.x = cos(Maths::toRadians(rotationAngle)) * unitsPerSecond;
				velocity.y = sin(Maths::toRadians(rotationAngle)) * unitsPerSecond;
			}

			inline void setVelocity(float unitsPerSecond, float angle)
			{
				velocity.x = cos(Maths::toRadians(angle)) * unitsPerSecond;
				velocity.y = sin(Maths::toRadians(angle)) * unitsPerSecond;
			}

			inline void setIterations(Types::byte it) { iterations = it; }
			inline void setMass(float newMass) { mass = newMass; }

			inline void rotate(float degrees) { rotationAngle += degrees; }

			inline void applyForce(float newtons, float angle)
			{
				force.x += cos(Maths::toRadians(angle)) * newtons;
				force.y += sin(Maths::toRadians(angle)) * newtons;
			}

			inline void accelerate(Maths::Vector2D acceleration/*, float angle = this->getRotation()*/)
			{
				velocity.x += cos(Maths::toRadians(rotationAngle)) * acceleration.x;
				velocity.y += sin(Maths::toRadians(rotationAngle)) * acceleration.y;
			}
		};

	}
}