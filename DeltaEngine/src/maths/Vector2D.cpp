#include "vector2d.h"

namespace DeltaEngine {
	namespace Maths {

		Vector2D::Vector2D(const float& x, const float& y)
		{
			this->x = x;
			this->y = y;
		}

		Vector2D& Vector2D::operator+=(const Vector2D& other)
		{
			x += other.x;
			y += other.y;
			return *this;
		}

		Vector2D& Vector2D::operator-=(const Vector2D& other)
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}

		Vector2D& Vector2D::operator*=(const Vector2D& other)
		{
			x *= other.x;
			y *= other.y;
			return *this;
		}

		Vector2D& Vector2D::operator/=(const Vector2D& other)
		{
			x /= other.x;
			y /= other.y;
			return *this;
		}

		Vector2D operator+(Vector2D left, const Vector2D& right)
		{
			left.x += right.x;
			left.y += right.y;
			return left;
		}

		Vector2D operator-(Vector2D left, const Vector2D& right)
		{
			left.x -= right.x;
			left.y -= right.y;
			return left;
		}

		Vector2D operator*(Vector2D left, const Vector2D& right)
		{
			left.x *= right.x;
			left.y *= right.y;
			return left;
		}

		Vector2D operator/(Vector2D left, const Vector2D& right)
		{
			left.x /= right.x;
			left.y /= right.y;
			return left;
		}

		Vector2D operator+(Vector2D left, const float right)
		{
			left.x += right;
			left.y += right;
			return left;
		}

		Vector2D operator-(Vector2D left, const float right)
		{
			left.x -= right;
			left.y -= right;
			return left;
		}

		Vector2D operator*(Vector2D left, const float right)
		{
			left.x *= right;
			left.y *= right;
			return left;
		}

		Vector2D operator/(Vector2D left, const float right)
		{
			left.x /= right;
			left.y /= right;
			return left;
		}

		std::ostream& operator<<(std::ostream& stream, const Vector2D& vector)
		{
			stream << "Vector2D: (" << vector.x << ", " << vector.y  << ")";
			return stream;
		}
	}
}