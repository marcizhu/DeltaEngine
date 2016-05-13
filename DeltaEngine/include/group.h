#pragma once

#include <vector>

#include "renderable2d.h"
#include "matrix4.h"

namespace DeltaEngine {
	namespace Graphics {

		class Group : public Renderable2D
		{
		private:
			std::vector<Renderable2D*> renderables;
			Maths::Matrix4 transformationMatrix;

		public:
			DELTAENGINE_API Group(const Maths::Matrix4& transform) : transformationMatrix(transform) { }
			DELTAENGINE_API ~Group();
			DELTAENGINE_API void add(Renderable2D* renderable);
			DELTAENGINE_API void submit(Renderer2D* renderer) const override;
		};

	}
}
