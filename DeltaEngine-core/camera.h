#pragma once

#ifndef __DELTAENGINE_CAMERA__
#define __DELTAENGINE_CAMERA__

#include "DeltaEngine.h"
#include "Matrix4.h"
#include "vector2d.h"
#include "renderable2d.h"

#undef near
#undef far

namespace DeltaEngine {
	namespace Graphics {

		class Camera {
		private:
			Maths::Matrix4 matrix;

			float sizeX, sizeY;

			float posX, posY;

		public:
			DELTAENGINE_API Camera(float left, float right, float top, float bottom, float near, float far);
			//DELTAENGINE_API Camera(float fov, float aspectRatio, float near, float far);

			DELTAENGINE_API void setRelativePosition(float dx = 0, float dy = 0);
			DELTAENGINE_API void setAbsolutePosition(float x, float y);

			DELTAENGINE_API void track(const Renderable2D& object, float left, float bottom);

			DELTAENGINE_API inline const Maths::Matrix4& getMatrix4() const { return matrix; };

			DELTAENGINE_API inline float getX() const { return posX; };
			DELTAENGINE_API inline float getY() const { return posY; };
			DELTAENGINE_API inline const void getPosition(float& x, float& y) const { x = posX; y = posY; };
			DELTAENGINE_API inline const Maths::Vector2D& getPosition() const { return Maths::Vector2D(posX, posY); };
		};

	}
}

#endif