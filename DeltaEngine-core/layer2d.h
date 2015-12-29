#pragma once

#include "DeltaEngine.h"

#include "renderer2d.h"
#include "renderable2d.h"
#include "matrix4.h"

namespace DeltaEngine {
	namespace Graphics {

		class Layer2D
		{
		protected:
			Renderer2D* renderer;
			std::vector<Renderable2D*> renderables;
			Shader* shader;
			Maths::Matrix4 projectionMatrix;
			//TODO: Implement cameras!
			//Maths::Matrix4 viewMatrix;

		public:
			DELTAENGINE_API Layer2D(Renderer2D* renderer, Shader* shader, const Maths::Matrix4& projectionMatrix);
			DELTAENGINE_API virtual ~Layer2D();
			DELTAENGINE_API inline virtual void add(Renderable2D* renderable) { renderables.push_back(renderable); };
			DELTAENGINE_API virtual void render();

			inline Renderable2D* operator[](Types::uint32 id) const { return renderables[id]; };
		};

	}
}