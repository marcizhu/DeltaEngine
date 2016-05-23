#pragma once

#include "renderable2d.h"
#include "aabb.h"
#include "log.h"

namespace DeltaEngine {
	namespace Physics {

		class PhysicsRenderable2D : public Graphics::Renderable2D
		{
		private:
			float angularVelocity;
			float rotationAngle; // in degrees!
			//float friction;
			float mass;
			Types::byte iterations;
			Maths::Vector2D force; // in units per second every second (u / s^2)
			Maths::Vector2D velocity; // in units per second (u / s)
			Maths::AABB aabb;

			void init(Graphics::Texture* texture, Types::byte iterations)
			{
				this->texture = texture;

				rotationAngle = angularVelocity = 0.0f;

				force = velocity = Maths::Vector2D(0, 0);

				this->iterations = iterations;
			}

		public:
			PhysicsRenderable2D(float x, float y, float width, float height, Types::Color color, float mass, Types::byte it)
				: Renderable2D(Maths::Vector2D(x, y), Maths::Vector2D(width, height), color), aabb(position, position + size), mass(mass)
			{ init(nullptr, it); };

			PhysicsRenderable2D(float x, float y, float width, float height, Types::uint32 color, float mass, Types::byte it)
				: Renderable2D(Maths::Vector2D(x, y), Maths::Vector2D(width, height), color), aabb(position, position + size), mass(mass)
			{ init(nullptr, it); };

			PhysicsRenderable2D(float x, float y, float width, float height, Graphics::Texture* texture, float mass, Types::byte it)
				: Renderable2D(Maths::Vector2D(x, y), Maths::Vector2D(width, height), 0xffffffff), aabb(position, position + size), mass(mass)
			{ init(texture, it); }

			void update(float dt)
			{
				position += velocity * dt + ((force / mass) * dt * dt * 0.5f);
				rotationAngle += angularVelocity * dt;

				velocity += (force / mass) * dt;

				// tunneling prevention
				if(abs(velocity.x * dt) >= size.x) DELTAENGINE_WARN("[Physics] Horizontal speed is too fast! (", velocity.x, ")");
				if(abs(velocity.y * dt) >= size.y) DELTAENGINE_WARN("[Physics] Vertical speed is too fast! (", velocity.y, ")");

				aabb = Maths::AABB(position, position + size);
			}

			inline bool needsUpdate() { return force.distance() != 0.0f || velocity.distance() != 0.0f; }

			inline float getMass() const { return mass; }
			inline float getForce() const { return force.distance(); }
			inline float getRotation() const { return rotationAngle; }
			inline float getAngularVelocity() const { return angularVelocity; }
			inline Types::byte getIterations() const { return iterations; }
			inline const Maths::Vector2D& getVelocity() const { return velocity; }
			inline const Maths::Vector2D& getAcceleration() const { return (force / mass); }

			inline const Maths::Vector2D& getLinearMomentum() const { return mass * velocity; }
			inline const Maths::Vector2D& getAngularMomentum() const { return (size / 2) * angularVelocity * (size / 2) * mass; }

			inline float getPotentialEnergy(float gravity) const { return mass * gravity * position.y; }
			inline float getKineticEnergy() const { return (mass * velocity.distance() * velocity.distance()) / 2.0f; }
			inline float getMechanicalEnergy(float gravity) const { return getKineticEnergy() + getPotentialEnergy(gravity); }

			inline void setRotation(float degrees) { rotationAngle = degrees; }
			inline void setAngularVelocity(float velocity) { angularVelocity = velocity; }

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

			inline void removeForce(float newtons, float angle)
			{
				force.x -= cos(Maths::toRadians(angle)) * newtons;
				force.y -= sin(Maths::toRadians(angle)) * newtons;
			}

			inline void applyImpulse(float impulse, float angle)
			{
				velocity.x += cos(Maths::toRadians(angle)) * impulse;
				velocity.y += sin(Maths::toRadians(angle)) * impulse;
			}
		};

	}
}