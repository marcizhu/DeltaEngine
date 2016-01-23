#pragma once

#include "DeltaEngine.h"

#include "renderer2d.h"
#include "renderable2d.h"
#include "matrix4.h"
#include "vector2d.h"
#include "shader.h"

namespace DeltaEngine {
	namespace Graphics {

		class Layer2D
		{
		protected:
			std::vector<Renderable2D*> renderables;
			Renderer2D* renderer;
			Shader* shader;
			Maths::Matrix4 projectionMatrix;
			Maths::Matrix4 viewMatrix;
			
			float xCamera;
			float yCamera;

			void setViewMatrix();

		public:
			DELTAENGINE_API Layer2D(Renderer2D* renderer, Shader* shader, const Maths::Matrix4& projectionMatrix);
			DELTAENGINE_API virtual ~Layer2D();
			DELTAENGINE_API inline virtual void add(Renderable2D* renderable) { renderables.push_back(renderable); };
			DELTAENGINE_API virtual void render();

			DELTAENGINE_API void setCameraPosition(float x, float y);
			DELTAENGINE_API inline const Maths::Matrix4& getCamera() const { return viewMatrix; };

			DELTAENGINE_API inline const Maths::Vector2D getCameraPosition() const { return Maths::Vector2D(xCamera, yCamera); }
			DELTAENGINE_API inline const float getCameraPositionX() const { return xCamera; }
			DELTAENGINE_API inline const float getCameraPositionY() const { return yCamera; }

			DELTAENGINE_API inline const std::vector<Renderable2D*>& getRenderables() const { return renderables; }

			DELTAENGINE_API void rotate(float angle, Maths::Vector3D axis);
			DELTAENGINE_API void rotate(float angle, float xAxis, float yAxis, float zAxis);

			inline Renderable2D* operator[](Types::uint32 id) const { return renderables[id]; };
		};

	}
}