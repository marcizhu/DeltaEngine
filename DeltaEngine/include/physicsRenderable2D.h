#pragma once

#include <Box2D\Box2D.h>

#include "internal.h"
#include "obb.h"
#include "log.h"
#include "texture.h"
#include "sprite.h"
#include "physicsRenderer2D.h"

namespace DeltaEngine {
	namespace Physics {

		//class PhysicsRenderer2D;

		class PhysicsRenderable2D
		{
		private:
			void setUVDefaults()
			{
				UV.push_back(Maths::Vector2D(0, 0));
				UV.push_back(Maths::Vector2D(0, 1));
				UV.push_back(Maths::Vector2D(1, 1));
				UV.push_back(Maths::Vector2D(1, 0));
			}

			//Maths::Vector2D position;
			Maths::Vector2D size;
			Types::uint32 color;
			std::vector<Maths::Vector2D> UV;
			Graphics::Texture* texture = nullptr;
			Graphics::Sprite sprites;

			b2Body* body = nullptr;
			float* data;

			DELTAENGINE_API void init(const Maths::Vector2D& pos, const Maths::Vector2D& size, Graphics::Texture* texture, float mass);

		public:
			PhysicsRenderable2D(float x, float y, float width, float height, Types::Color color, float mass) : color(color.getABGRColor()) { init(Maths::Vector2D(x, y), Maths::Vector2D(width, height), nullptr, mass); };
			PhysicsRenderable2D(float x, float y, float width, float height, Graphics::Texture* texture, float mass) : color(0xffffffff) { init(Maths::Vector2D(x, y), Maths::Vector2D(width, height), texture, mass); }
			PhysicsRenderable2D(float x, float y, float width, float height, Types::uint32 color, float mass) : color(color) { init(Maths::Vector2D(x, y), Maths::Vector2D(width, height), nullptr, mass); };

			virtual ~PhysicsRenderable2D() {}

			virtual void submit(PhysicsRenderer2D* renderer) const { renderer->submit(this); }
			virtual void submit(PhysicsRenderer2D* renderer, bool transformationStack) const { renderer->submit(this, transformationStack); }

			inline const Maths::Vector2D getPosition() const { return Maths::Vector2D(body->GetPosition()); }
			inline const Maths::Vector2D& getSize() const { return size; }
			inline const Types::uint32 getColor() const { return color; }
			inline const std::vector<Maths::Vector2D>& getUV() const { return UV; }
			inline const GLuint getTextureID() const { return sprites.getTextureCount() ? sprites.getCurrentTexture()->getID() : texture ? texture->getID() : 0; }
			inline Graphics::Sprite& getSprite() { return sprites; }
			inline const Graphics::Texture* getTexture() const { return sprites.getTextureCount() ? sprites.getCurrentTexture() : texture ? texture : nullptr; }

			inline void setColor(Types::uint32 color) { this->color = color; }
			inline void setColor(Types::Color& color) { this->color = color.getABGRColor(); };

			inline const void setBody(b2Body* b) { body = b; }

			inline b2Body* getBody() { return body; }

			inline const float* getData() const { return data; }

			inline float getMass() const { return body->GetMass(); }
			inline float getRotation() const { return body->GetAngle(); }
			inline float getAngularVelocity() const { return body->GetAngularVelocity(); }
			inline const Maths::Vector2D& getVelocity() const { return Maths::Vector2D(body->GetLinearVelocity()); }

			inline void setAngularVelocity(float velocity) { body->SetAngularVelocity(velocity); }

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

			inline void setMass(float newMass) {}

			inline void rotate(float degrees) {}

			inline void applyForce(float newtons, float angle)
			{

			}

			inline void applyImpulse(float impulse, float angle)
			{
				body->ApplyLinearImpulseToCenter(b2Vec2(cos(angle) * impulse, sin(angle) * impulse), true);
			}
		};

	}
}