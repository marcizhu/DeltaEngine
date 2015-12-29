#include "matrix4.h"
#include "vector2d.h"
#include "vector3d.h"
#include "vector4d.h"
#include "maths.h"

namespace DeltaEngine {
	namespace Maths {

		Matrix4::Matrix4()
		{
			for (int i = 0; i < 4 * 4; i++)
				elements[i] = 0.0f;
		}

		Matrix4::Matrix4(float diagonal)
		{
			for (int i = 0; i < 4 * 4; i++)
				elements[i] = 0.0f;

			elements[0 + 0 * 4] = diagonal;
			elements[1 + 1 * 4] = diagonal;
			elements[2 + 2 * 4] = diagonal;
			elements[3 + 3 * 4] = diagonal;
		}

		Matrix4 Matrix4::identity()
		{
			return Matrix4(1.0f);
		}

		Matrix4& Matrix4::multiply(const Matrix4& other)
		{
			float data[16];

			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					float sum = 0.0f;
					
					for (int e = 0; e < 4; e++) 
						sum += elements[x + e * 4] * other.elements[e + y * 4];

					data[x + y * 4] = sum;
				}
			}
			
			memcpy(elements, data, 4 * 4 * sizeof(float));
			return *this;
		}

		Vector2D Matrix4::multiply(const Vector2D& other) const
		{
			return Vector2D(
				columns[0].x * other.x + columns[1].x * other.y + columns[2].x + columns[3].x,
				columns[0].y * other.x + columns[1].y * other.y + columns[2].y + columns[3].y);
		}

		Vector3D Matrix4::multiply(const Vector3D& other) const
		{
			return Vector3D(
				columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z + columns[3].x,
				columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z + columns[3].y,
				columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z + columns[3].z);
		}
		
		Vector4D Matrix4::multiply(const Vector4D& other) const
		{
			return Vector4D(
				columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z + columns[3].x * other.w,
				columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z + columns[3].y * other.w,
				columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z + columns[3].z * other.w,
				columns[0].w * other.x + columns[1].w * other.y + columns[2].w * other.z + columns[3].w * other.w);
		}

		Matrix4 operator*(Matrix4 left, const Matrix4& right)
		{
			return left.multiply(right);
		}

		Vector2D operator*(const Matrix4& left, const Vector2D& right)
		{
			return left.multiply(right);
		}

		Vector3D operator*(const Matrix4& left, const Vector3D& right)
		{
			return left.multiply(right);
		}
		
		Vector4D operator*(const Matrix4& left, const Vector4D& right)
		{
			return left.multiply(right);
		}

		Matrix4& Matrix4::operator*=(const Matrix4& other)
		{
			return multiply(other);
		}

		Matrix4 Matrix4::orthographic(float left, float right, float top, float bottom, float near, float far)
		{
			Matrix4 result(1.0f);

			result.elements[0 + 0 * 4] = 2.0f / (right - left);
			result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
			result.elements[2 + 2 * 4] = 2.0f / (near - far);

			result.elements[0 + 3 * 4] = (left + right) / (left - right);
			result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
			result.elements[2 + 3 * 4] = (far + near) / (far - near);

			return result;
		}

		Matrix4 Matrix4::perspective(float fov, float aspectRatio, float near, float far)
		{
			Matrix4 result(1.0f);

			float q = 1.0f / tan(toRadians(0.5f * fov));
			float a = q / aspectRatio;

			float b = (near + far) / (near - far);
			float c = (2.0f * near * far) / (near - far);

			result.elements[0 + 0 * 4] = a;
			result.elements[1 + 1 * 4] = q;
			result.elements[2 + 2 * 4] = b;
			result.elements[3 + 2 * 4] = -1.0f;
			result.elements[2 + 3 * 4] = c;

			return result;
		}

		void Matrix4::translate(const Vector3D& translation)
		{
			this->elements[0 + 3 * 4] = translation.x;
			this->elements[1 + 3 * 4] = translation.y;
			this->elements[2 + 3 * 4] = translation.z;
		}

		void Matrix4::translate(float x, float y, float z)
		{
			this->elements[0 + 3 * 4] = x;
			this->elements[1 + 3 * 4] = y;
			this->elements[2 + 3 * 4] = z;
		}

		void Matrix4::rotate(float angle, const Vector3D& axis)
		{
			float c = cos(toRadians(angle));
			float s = sin(toRadians(angle));
			float omc = 1.0f - c;

			float x = axis.x;
			float y = axis.y;
			float z = axis.z;

			this->elements[0 + 0 * 4] = x * omc + c;
			this->elements[1 + 0 * 4] = y * x * omc + z * s;
			this->elements[2 + 0 * 4] = x * z * omc - y * s;
			
			this->elements[0 + 1 * 4] = x * y * omc - z * s;
			this->elements[1 + 1 * 4] = y * omc + c;
			this->elements[2 + 1 * 4] = y * z * omc + x * s;
			
			this->elements[0 + 2 * 4] = x * z * omc + y * s;
			this->elements[1 + 2 * 4] = y * z * omc - x * s;
			this->elements[2 + 2 * 4] = z * omc + c;
		}

		void Matrix4::rotate(float angle, float xAxis, float yAxis, float zAxis)
		{
			float c = cos(toRadians(angle));
			float s = sin(toRadians(angle));
			float omc = 1.0f - c;


			this->elements[0 + 0 * 4] = xAxis * omc + c;
			this->elements[1 + 0 * 4] = yAxis * xAxis * omc + zAxis * s;
			this->elements[2 + 0 * 4] = xAxis * zAxis * omc - yAxis * s;

			this->elements[0 + 1 * 4] = xAxis * yAxis * omc - zAxis * s;
			this->elements[1 + 1 * 4] = yAxis * omc + c;
			this->elements[2 + 1 * 4] = yAxis * zAxis * omc + xAxis * s;

			this->elements[0 + 2 * 4] = xAxis * zAxis * omc + yAxis * s;
			this->elements[1 + 2 * 4] = yAxis * zAxis * omc - xAxis * s;
			this->elements[2 + 2 * 4] = zAxis * omc + c;
		}

		void Matrix4::scale(const Vector3D& scale)
		{
			this->elements[0 + 0 * 4] = scale.x;
			this->elements[1 + 1 * 4] = scale.y;
			this->elements[2 + 2 * 4] = scale.z;
		}

		void Matrix4::scale(float x, float y, float z)
		{
			this->elements[0 + 0 * 4] = x;
			this->elements[1 + 1 * 4] = y;
			this->elements[2 + 2 * 4] = z;
		}

		Vector4D Matrix4::getColumn(int index) const
		{
			index *= 4;
			return Vector4D(elements[index], elements[index + 1], elements[index + 2], elements[index + 3]);
		}
	}
}