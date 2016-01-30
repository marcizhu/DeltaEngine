#pragma once

#include <iostream>

#include "internal.h"

namespace DeltaEngine {
	namespace Maths {

		class Vector3D {
		public:
			float x, y, z;

			DELTAENGINE_API Vector3D(const float& x, const float& y, const float& z);
			DELTAENGINE_API inline Vector3D() { x = y = z = 0.0f; };

			DELTAENGINE_API friend Vector3D operator+(Vector3D left, const Vector3D& right);
			DELTAENGINE_API friend Vector3D operator-(Vector3D left, const Vector3D& right);
			DELTAENGINE_API friend Vector3D operator*(Vector3D left, const Vector3D& right);
			DELTAENGINE_API friend Vector3D operator/(Vector3D left, const Vector3D& right);

			DELTAENGINE_API Vector3D& operator+=(const Vector3D& other);
			DELTAENGINE_API Vector3D& operator-=(const Vector3D& other);
			DELTAENGINE_API Vector3D& operator*=(const Vector3D& other);
			DELTAENGINE_API Vector3D& operator/=(const Vector3D& other);

			DELTAENGINE_API bool operator==(const Vector3D& other) { return x == other.x && y == other.y && z == other.z; };
			DELTAENGINE_API bool Vector3D::operator!=(const Vector3D& other) { return !(*this == other); }

			DELTAENGINE_API friend std::ostream& operator<<(std::ostream& stream, const Vector3D& vector);
		};

	}
}