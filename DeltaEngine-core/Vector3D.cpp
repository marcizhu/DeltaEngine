#include "vector3d.h"

namespace DeltaEngine {
	namespace Maths {

		Vector3D::Vector3D(const float & x, const float & y, const float & z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		Vector3D& Vector3D::operator+=(const Vector3D & other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		Vector3D& Vector3D::operator-=(const Vector3D & other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		Vector3D& Vector3D::operator*=(const Vector3D & other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			return *this;
		}

		Vector3D& Vector3D::operator/=(const Vector3D & other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			return *this;
		}

		Vector3D operator+(Vector3D left, const Vector3D& right)
		{
			left.x += right.x;
			left.y += right.y;
			left.z += right.z;
			return left;
		}

		Vector3D operator-(Vector3D left, const Vector3D & right)
		{
			left.x -= right.x;
			left.y -= right.y;
			left.z -= right.z;
			return left;
		}

		Vector3D operator*(Vector3D left, const Vector3D & right)
		{
			left.x *= right.x;
			left.y *= right.y;
			left.z *= right.z;
			return left;
		}

		Vector3D operator/(Vector3D left, const Vector3D & right)
		{
			left.x /= right.x;
			left.y /= right.y;
			left.z /= right.z;
			return left;
		}

		std::ostream & operator<<(std::ostream& stream, const Vector3D& vector)
		{
			stream << "Vector3D: (" << vector.x << ", " << vector.y << ", " << vector.z << ")";
			return stream;
		}
	}
}