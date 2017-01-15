#pragma once

#include "physicsRenderable2d.h"

namespace DeltaEngine {
	namespace Physics {

		class StaticBody : public PhysicsRenderable2D
		{
		private:
			float friction;

		protected:
			DELTAENGINE_API void createBody() override;

		public:
			StaticBody(float x, float y, float width, float height, Types::Color color, float friction) : PhysicsRenderable2D(x, y, width, height, color, 0.0f) { this->friction = friction; }
			StaticBody(float x, float y, float width, float height, Graphics::Texture* texture, float friction) : PhysicsRenderable2D(x, y, width, height, texture, 0.0f) { this->friction = friction; }
			StaticBody(float x, float y, float width, float height, Types::uint32 color, float friction) : PhysicsRenderable2D(x, y, width, height, color, 0.0f) { this->friction = friction; }

			float getFriction() const { return friction; }
		};

	}
}