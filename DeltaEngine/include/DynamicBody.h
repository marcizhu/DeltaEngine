#pragma once

#include "physicsRenderable2d.h"

namespace DeltaEngine {
	namespace Physics {

		class DynamicBody : public PhysicsRenderable2D
		{
		protected:
			DELTAENGINE_API void createBody() override;

		public:
			DynamicBody(float x, float y, float width, float height, Types::Color color, float mass) : PhysicsRenderable2D(x, y, width, height, color, 0.0f) { }
			DynamicBody(float x, float y, float width, float height, Graphics::Texture* texture, float mass) : PhysicsRenderable2D(x, y, width, height, texture, 0.0f) { }
			DynamicBody(float x, float y, float width, float height, Types::uint32 color, float mass) : PhysicsRenderable2D(x, y, width, height, color, 0.0f) { }
		};

	}
}