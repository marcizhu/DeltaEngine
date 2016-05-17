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
			bool limits;
			Maths::AABB area;
			float gravity;

		public:
			DELTAENGINE_API World2D(Graphics::Renderer2D* renderer, Graphics::Shader* shader, const Maths::Matrix4& projectionMatrix, float gravity)
				: Layer2D(renderer, shader, projectionMatrix), gravity(gravity), limits(true)
			{
				// We assume it is an orthographic matrix
				area = projectionMatrix.orthographicToAABB();
			}

			DELTAENGINE_API Graphics::Renderable2D* add(Graphics::Renderable2D* object) override;

			DELTAENGINE_API void update(float timestep);

			DELTAENGINE_API void setLimits(bool enable) { limits = enable; }
		};

	}
}