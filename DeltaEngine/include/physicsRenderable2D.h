#pragma once

#include <Box2D\Box2D.h>

#include "internal.h"
#include "renderable2d.h"
#include "obb.h"
#include "log.h"

namespace DeltaEngine {
	namespace Physics {

		class PhysicsRenderable2D : public Graphics::Renderable2D
		{
		private:
			b2Body* body = nullptr;
			float* data;

			DELTAENGINE_API void init(Graphics::Texture* texture, float mass);

		public:
			PhysicsRenderable2D(float x, float y, float width, float height, Types::Color color, float mass)
				: Renderable2D(Maths::Vector2D(x, y), Maths::Vector2D(width, height), color)
			{ init(nullptr, mass); };

			PhysicsRenderable2D(float x, float y, float width, float height, Types::uint32 color, float mass)
				: Renderable2D(Maths::Vector2D(x, y), Maths::Vector2D(width, height), color)
			{ init(nullptr, mass); };

			PhysicsRenderable2D(float x, float y, float width, float height, Graphics::Texture* texture, float mass)
				: Renderable2D(Maths::Vector2D(x, y), Maths::Vector2D(width, height), 0xffffffff)
			{ init(texture, mass); }

			void update(float dt)
			{
				//if (obb.intersects(Maths::OBB2D(Maths::Vector2D(8.0f, 1.0f), 16.0f, 2.0f, 0.0f))) return;

				//position += velocity * dt + ((force / mass) * dt * dt * 0.5f);
				//rotationAngle += angularVelocity * dt;

				//velocity += (force / mass) * dt;

				//obb = Maths::OBB2D(position, size, rotationAngle);

				// tunneling prevention
				//if(abs(velocity.x * dt) >= size.x) DELTAENGINE_WARN("[Physics] Horizontal speed is too fast! (", velocity.x, ")");
				//if(abs(velocity.y * dt) >= size.y) DELTAENGINE_WARN("[Physics] Vertical speed is too fast! (", velocity.y, ")");
			}

			inline const void setBody(b2Body* b) { body = b; }

			inline b2Body* getBody() { return body; }

			inline const float* getData() const { return data; }

			inline const Maths::Vector2D getPositionEx() const { return Maths::Vector2D(body->GetPosition().x, body->GetPosition().y); }
			inline float getMass() const {  }
			inline float getForce() const {  }
			inline float getRotation() const { return body->GetAngle(); }
			inline float getAngularVelocity() const {  }
			inline Types::byte getIterations() const {  }
			inline const Maths::Vector2D& getVelocity() const {  }
			inline const Maths::Vector2D& getAcceleration() const {  }

			inline void setRotation(float degrees) { }
			inline void setAngularVelocity(float velocity) {  }

			inline void setAcceleration(float unitsPerSecond)
			{
				
			}

			inline void setAcceleration(float unitsPerSecond, float angle)
			{
				
			}

			inline void setVelocity(float unitsPerSecond)
			{
				
			}

			inline void setVelocity(float unitsPerSecond, float angle)
			{
				
			}

			inline void setMass(float newMass) {  }

			inline void rotate(float degrees) {  }

			inline void applyForce(float newtons, float angle)
			{
				
			}

			inline void removeForce(float newtons, float angle)
			{
				
			}

			inline void applyImpulse(float impulse, float angle)
			{
				
			}
		};

	}
}