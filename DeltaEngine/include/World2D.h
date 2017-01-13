#pragma once

#include <vector>

#include "internal.h"
#include "physicsRenderable2D.h"
#include "shader.h"

namespace DeltaEngine {
	namespace Physics {

		class World2D
		{
		private:
			std::vector<PhysicsRenderable2D*> renderables;
			PhysicsRenderer2D* renderer;
			Graphics::Shader* shader;
			Maths::Matrix4 projectionMatrix;
			Maths::Matrix4 viewMatrix;

			float xCamera;
			float yCamera;

			void setViewMatrix();

			b2World* world;
			Maths::Vector2D gravity;

		public:
			DELTAENGINE_API World2D(Graphics::Shader* shader, Maths::Matrix4 pr_matrix, const Maths::Vector2D& gravity);
			DELTAENGINE_API ~World2D();

			DELTAENGINE_API inline PhysicsRenderable2D* add(PhysicsRenderable2D* object);

			DELTAENGINE_API void step(float timestep, int vIterations, int posIterations);

			DELTAENGINE_API inline void remove(PhysicsRenderable2D* renderable);
			DELTAENGINE_API virtual void render();

			DELTAENGINE_API void setCameraPosition(float x, float y);
			DELTAENGINE_API inline const Maths::Matrix4& getCamera() const { return viewMatrix; };

			DELTAENGINE_API inline const Maths::Vector2D getCameraPosition() const { return Maths::Vector2D(xCamera, yCamera); }
			DELTAENGINE_API inline const float getCameraPositionX() const { return xCamera; }
			DELTAENGINE_API inline const float getCameraPositionY() const { return yCamera; }

			DELTAENGINE_API inline const PhysicsRenderable2D* getRenderable(Types::uint32 index) const { return renderables[index]; }

			DELTAENGINE_API void rotate(float angle, Maths::Vector3D axis);
			DELTAENGINE_API void rotate(float angle, float xAxis, float yAxis, float zAxis);

			DELTAENGINE_API inline PhysicsRenderable2D* operator[](Types::uint32 id) const { return renderables[id]; };

			DELTAENGINE_API const Maths::Vector2D& getGravity() { return gravity; }
		};

	}
}