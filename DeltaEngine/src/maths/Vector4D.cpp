#include <sstream>

#include "vector4d.h"

namespace DeltaEngine {
	namespace Maths {

		Vector4D::Vector4D(const float & x, const float & y, const float & z, const float & w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		Vector4D& Vector4D::operator+=(const Vector4D & other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
			return *this;
		}

		Vector4D& Vector4D::operator-=(const Vector4D & other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
			return *this;
		}

		Vector4D& Vector4D::operator*=(const Vector4D & other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			w *= other.w;
			return *this;
		}

		Vector4D& Vector4D::operator/=(const Vector4D & other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			w /= other.w;
			return *this;
		}

		Vector4D operator+(Vector4D left, const Vector4D& right)
		{
			left.x += right.x;
			left.y += right.y;
			left.z += right.z;
			left.w += right.w;
			return left;
		}

		Vector4D operator-(Vector4D left, const Vector4D & right)
		{
			left.x -= right.x;
			left.y -= right.y;
			left.z -= right.z;
			left.w -= right.w;
			return left;
		}

		Vector4D operator*(Vector4D left, const Vector4D & right)
		{
			left.x *= right.x;
			left.y *= right.y;
			left.z *= right.z;
			left.w *= right.w;
			return left;
		}

		Vector4D operator/(Vector4D left, const Vector4D & right)
		{
			left.x /= right.x;
			left.y /= right.y;
			left.z /= right.z;
			left.w /= right.w;
			return left;
		}

		Vector4D operator+(Vector4D left, const float right)
		{
			left.x += right;
			left.y += right;
			left.z += right;
			left.w += right;
			return left;
		}

		Vector4D operator-(Vector4D left, const float right)
		{
			left.x -= right;
			left.y -= right;
			left.z -= right;
			left.w -= right;
			return left;

		}

		Vector4D operator*(Vector4D left, const float right)
		{
			left.x *= right;
			left.y *= right;
			left.z *= right;
			left.w *= right;
			return left;
		}

		Vector4D operator/(Vector4D left, const float right)
		{
			left.x /= right;
			left.y /= right;
			left.z /= right;
			left.w /= right;
			return left;
		}

		std::ostream& operator<<(std::ostream& stream, const Vector4D& vector)
		{
			stream << "Vector4D: (" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
			return stream;
		}

		std::string Vector4D::toString() const
		{
			std::stringstream stream;

			stream << "Vector4D: (" << x << ", " << y << ", " << z << ", " << w << ")";

			return stream.str();
		}
	}
}