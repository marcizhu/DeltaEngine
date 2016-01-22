#pragma once

#include <iostream>

#include "DeltaEngine.h"

namespace DeltaEngine {
	namespace Maths {

		class Vector4D {
		public:
			float x, y, z, w;

			DELTAENGINE_API Vector4D(const float& x, const float& y, const float& z, const float& w);
			DELTAENGINE_API inline Vector4D() { x = y = z = w = 0.0f; };

			DELTAENGINE_API friend Vector4D operator+(Vector4D left, const Vector4D& right);
			DELTAENGINE_API friend Vector4D operator-(Vector4D left, const Vector4D& right);
			DELTAENGINE_API friend Vector4D operator*(Vector4D left, const Vector4D& right);
			DELTAENGINE_API friend Vector4D operator/(Vector4D left, const Vector4D& right);

			DELTAENGINE_API Vector4D& operator+=(const Vector4D& other);
			DELTAENGINE_API Vector4D& operator-=(const Vector4D& other);
			DELTAENGINE_API Vector4D& operator*=(const Vector4D& other);
			DELTAENGINE_API Vector4D& operator/=(const Vector4D& other);

			DELTAENGINE_API bool operator==(const Vector4D& other) { return x == other.x && y == other.y && z == other.z && w == other.w; };
			DELTAENGINE_API bool Vector4D::operator!=(const Vector4D& other) { return !(*this == other); }

			DELTAENGINE_API friend std::ostream& operator<<(std::ostream& stream, const Vector4D& vector);
		};

	}
}