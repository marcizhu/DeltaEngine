#pragma once

#include "renderable2d.h"
#include "aabb.h"
#include "log.h"

namespace DeltaEngine {
	namespace Graphics {

		class PhysicsRenderable2D : public Renderable2D
		{
		private:
			float rotationAngle; // in degrees!
			Maths::Vector2D acceleration; // in units per second every second (u / s^2)
			Maths::Vector2D velocity; // in units per second (u / s)
			Maths::AABB aabb;

		public:
			PhysicsRenderable2D(float x, float y, float width, float height, Types::Color color)
				: Renderable2D(Maths::Vector2D(x, y), Maths::Vector2D(width, height), color), aabb(position, position + size)
			{ this->texture = nullptr; rotationAngle = 0.0f; acceleration = velocity = Maths::Vector2D(0, 0); };

			PhysicsRenderable2D(float x, float y, float width, float height, Types::uint32 color)
				: Renderable2D(Maths::Vector2D(x, y), Maths::Vector2D(width, height), color), aabb(position, position + size)
			{ this->texture = nullptr; rotationAngle = 0.0f; acceleration = velocity = Maths::Vector2D(0, 0); };

			PhysicsRenderable2D(float x, float y, float width, float height, Texture* texture)
				: Renderable2D(Maths::Vector2D(x, y), Maths::Vector2D(width, height), 0xffffffff), aabb(position, position + size)
			{ this->texture = texture; rotationAngle = 0.0f; acceleration = velocity = Maths::Vector2D(0, 0); }

			PhysicsRenderable2D(float x, float y, float width, float height, Sprite sprite)
				: Renderable2D(Maths::Vector2D(x, y), Maths::Vector2D(width, height), 0xffffffff), aabb(position, position + size)
			{ this->texture = nullptr; rotationAngle = 0.0f; acceleration = velocity = Maths::Vector2D(0, 0); }

			void update(float dt)
			{
				velocity += acceleration * dt;

				// tunneling
				if((velocity.x * dt) >= size.x) DELTAENGINE_WARN("[Physics] Horizontal speed is too fast! (", velocity.x * dt,")");
				if((velocity.y * dt) >= size.y) DELTAENGINE_WARN("[Physics] Vertical speed is too fast! (", velocity.y * dt, ")");

				position += velocity * dt + (acceleration * dt * dt / 2.0f);

				aabb = Maths::AABB(position, position + size);
			}

			inline float getRotation() const { return rotationAngle; }
			inline Maths::Vector2D getAcceleration() const { return acceleration; }
			inline Maths::Vector2D getVelocity() const { return velocity; }

			inline void setRotation(float degrees) { rotationAngle = degrees; }
			inline void setAcceleration(float unitsPerSecond)
			{
				acceleration.x = cos(Maths::toRadians(rotationAngle)) * unitsPerSecond;
				acceleration.y = sin(Maths::toRadians(rotationAngle)) * unitsPerSecond;
			}
			inline void setAcceleration(float unitsPerSecond, float angle)
			{
				acceleration.x = cos(Maths::toRadians(angle)) * unitsPerSecond;
				acceleration.y = sin(Maths::toRadians(angle)) * unitsPerSecond;
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

			inline void rotate(float degrees) { rotationAngle += degrees; }
			inline void accelerate(Maths::Vector2D acceleration/*, float angle = this->getRotation()*/)
			{
				velocity.x += cos(Maths::toRadians(rotationAngle)) * acceleration.x;
				velocity.y += sin(Maths::toRadians(rotationAngle)) * acceleration.y;
			}
		};

	}
}