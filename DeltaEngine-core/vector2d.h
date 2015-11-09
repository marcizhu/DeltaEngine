#pragma once

#ifndef __DELTAENGINE_VECTOR_2D__
#define __DELTAENGINE_VECTOR_2D__

#include <iostream>

#include "DeltaEngine.h"

namespace DeltaEngine {
	namespace Maths {

		class Vector2D {

		public:
			float x, y;

			DELTAENGINE_API Vector2D(const float& x, const float& y);
			DELTAENGINE_API inline Vector2D() { x = y = 0.0f; };

			DELTAENGINE_API friend Vector2D operator+(Vector2D left, const Vector2D& right);
			DELTAENGINE_API friend Vector2D operator-(Vector2D left, const Vector2D& right);
			DELTAENGINE_API friend Vector2D operator*(Vector2D left, const Vector2D& right);
			DELTAENGINE_API friend Vector2D operator/(Vector2D left, const Vector2D& right);

			DELTAENGINE_API Vector2D& operator+=(const Vector2D& other);
			DELTAENGINE_API Vector2D& operator-=(const Vector2D& other);
			DELTAENGINE_API Vector2D& operator*=(const Vector2D& other);
			DELTAENGINE_API Vector2D& operator/=(const Vector2D& other);

			DELTAENGINE_API bool operator==(const Vector2D& other) { return x == other.x && y == other.y; };
			DELTAENGINE_API bool Vector2D::operator!=(const Vector2D& other) { return !(*this == other); }

			DELTAENGINE_API friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vector);
		};

	}
}

#endif