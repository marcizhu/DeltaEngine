#pragma once

#ifndef __DELTAENGINE_MATRIX4__
#define __DELTAENGINE_MATRIX4__

#include "DeltaEngine.h"

#include "vector3d.h"
#include "vector4d.h"

namespace DeltaEngine {
	namespace Maths {

		class Matrix4
		{
		private:
			Matrix4& multiply(const Matrix4& other);

		public:
			union
			{
				float elements[4 * 4];
				Vector4D columns[4];
			};

			DELTAENGINE_API Matrix4();
			DELTAENGINE_API Matrix4(float diagonal);

			DELTAENGINE_API Vector4D getColumn(int index) const;

			DELTAENGINE_API static Matrix4 identity();

			DELTAENGINE_API friend Matrix4 operator*(Matrix4 left, const Matrix4& right);
			DELTAENGINE_API Matrix4& operator*=(const Matrix4& other);

			DELTAENGINE_API static Matrix4 orthographic(float left, float right, float bottom, float top, float near, float far);
			DELTAENGINE_API static Matrix4 perspective(float fov, float aspectRatio, float near, float far);

			DELTAENGINE_API static Matrix4 translate(const Vector3D& translation);
			DELTAENGINE_API static Matrix4 rotate(float angle, const Vector3D& axis);
			DELTAENGINE_API static Matrix4 scale(const Vector3D& scale);
		};

	}
}

#endif