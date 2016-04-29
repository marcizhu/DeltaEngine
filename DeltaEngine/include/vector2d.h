#pragma once

#include <iostream>

#include "internal.h"

namespace DeltaEngine {
	namespace Maths {

		class Vector2D
		{
		public:
			float x, y;

			DELTAENGINE_API Vector2D(const float& x, const float& y);
			DELTAENGINE_API inline Vector2D() { x = y = 0.0f; }

			DELTAENGINE_API friend Vector2D operator+(Vector2D left, const Vector2D& right);
			DELTAENGINE_API friend Vector2D operator-(Vector2D left, const Vector2D& right);
			DELTAENGINE_API friend Vector2D operator*(Vector2D left, const Vector2D& right);
			DELTAENGINE_API friend Vector2D operator/(Vector2D left, const Vector2D& right);

			DELTAENGINE_API friend Vector2D operator+(Vector2D left, const float right);
			DELTAENGINE_API friend Vector2D operator-(Vector2D left, const float right);
			DELTAENGINE_API friend Vector2D operator*(Vector2D left, const float right);
			DELTAENGINE_API friend Vector2D operator/(Vector2D left, const float right);

			DELTAENGINE_API Vector2D& operator+=(const Vector2D& other);
			DELTAENGINE_API Vector2D& operator-=(const Vector2D& other);
			DELTAENGINE_API Vector2D& operator*=(const Vector2D& other);
			DELTAENGINE_API Vector2D& operator/=(const Vector2D& other);

			DELTAENGINE_API inline bool operator==(const Vector2D& other) const { return x == other.x && y == other.y; }
			DELTAENGINE_API inline bool operator!=(const Vector2D& other) const { return !(*this == other); }
			DELTAENGINE_API inline bool operator>=(const Vector2D& other) const { return x >= other.x && y >= other.y; }
			DELTAENGINE_API inline bool operator<=(const Vector2D& other) const { return x <= other.x && y <= other.y; }
			DELTAENGINE_API inline bool operator>(const Vector2D& other) const { return x > other.x && y > other.y; }
			DELTAENGINE_API inline bool operator<(const Vector2D& other) const { return x < other.x && y < other.y; }

			DELTAENGINE_API friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vector);
		};

	}
}