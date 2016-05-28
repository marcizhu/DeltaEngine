#pragma once

#include "internal.h"

#include "vector2d.h"
#include "vector3d.h"
#include "vector4d.h"
#include "aabb.h"

namespace DeltaEngine {
	namespace Maths {

		class Matrix4
		{
		private:
			Matrix4& multiply(const Matrix4& other);
			Vector2D multiply(const Vector2D& other) const;
			Vector3D multiply(const Vector3D& other) const;
			Vector4D multiply(const Vector4D& other) const;

		public:
			union
			{
				float elements[4 * 4];
				Vector4D columns[4];
			};

			DELTAENGINE_API Matrix4();
			DELTAENGINE_API Matrix4(float diagonal);

			DELTAENGINE_API static Matrix4 identity();

			DELTAENGINE_API friend Matrix4 operator*(Matrix4 left, const Matrix4& right);
			DELTAENGINE_API friend Vector2D operator*(const Matrix4& left, const Vector2D& right);
			DELTAENGINE_API friend Vector3D operator*(const Matrix4& left, const Vector3D& right);
			DELTAENGINE_API friend Vector4D operator*(const Matrix4& left, const Vector4D& right);

			DELTAENGINE_API Matrix4& operator*=(const Matrix4& other);

			DELTAENGINE_API static Matrix4 orthographic(float left, float right, float top, float bottom);
			DELTAENGINE_API static Matrix4 perspective(float fov, float aspectRatio, float near, float far);

			DELTAENGINE_API const Matrix4& translate(const Vector3D& translation);
			DELTAENGINE_API const Matrix4& rotate(float angle, const Vector3D& axis);
			DELTAENGINE_API const Matrix4& scale(const Vector3D& scale);

			DELTAENGINE_API const Matrix4& translate(float x, float y, float z);
			DELTAENGINE_API const Matrix4& rotate(float angle, float xAxis, float yAxis, float zAxis);
			DELTAENGINE_API const Matrix4& scale(float x, float y, float z);

			DELTAENGINE_API const AABB& orthographicToAABB() const;

			DELTAENGINE_API const signed int getDownDirection() const;
			DELTAENGINE_API const signed int getUpDirection() const;
			DELTAENGINE_API const signed int getLeftDirection() const;
			DELTAENGINE_API const signed int getRightDirection() const;
		};

	}
}