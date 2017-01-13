#pragma once

#include <vector>

#include "internal.h"
#include "physicsRenderable2D.h"
#include "layer2d.h"

namespace DeltaEngine {
	namespace Physics {

		class World2D : public Graphics::Layer2D
		{
		private:
			b2World* world;
			Maths::Vector2D gravity;

		public:
			DELTAENGINE_API World2D(Graphics::Renderer2D* renderer, Graphics::Shader* shader, const Maths::Matrix4& projectionMatrix, const Maths::Vector2D& gravity);

			DELTAENGINE_API Graphics::Renderable2D* add(Graphics::Renderable2D* object) override;

			DELTAENGINE_API void step(float timestep, int vIterations, int posIterations);

			DELTAENGINE_API const Maths::Vector2D& getGravity() { return gravity; }
		};

	}
}