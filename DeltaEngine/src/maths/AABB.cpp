#include "aabb.h"
#include "maths.h"
#include "vector2d.h"
#include "vector3d.h"
#include "log.h"

#if defined(min) || defined(max)
#	undef min
#	undef max
#endif

namespace DeltaEngine {
	namespace Maths {

		AABB2D::AABB2D(const Vector2D& min, const Vector2D& max)
		{
			this->min.x = Maths::min<float>(min.x, max.x);
			this->min.y = Maths::min<float>(min.y, max.y);

			this->max.x = Maths::max<float>(min.x, max.x);
			this->max.y = Maths::max<float>(min.y, max.y);

			DELTAENGINE_ASSERT(this->min < this->max);
		}

		bool AABB2D::contains(const Vector2D& point) const
		{
			return (point >= min && point <= max);
		}

		bool AABB2D::intersects(const AABB2D& other) const
		{
			return (max > other.min && min < other.max); //|| (min > other.max && max < other.min);
		}

		const Vector2D AABB2D::getCenter() const
		{
			return min + (max - min) / 2.0f;
		}

		bool AABB2D::operator==(const AABB2D& other) const
		{
			return (min == other.min && max == other.max);
		}

		bool AABB2D::operator!=(const AABB2D& other) const
		{
			return !(*this == other);
		}

		bool AABB2D::operator<=(const AABB2D& other) const
		{
			return (max < other.min);
		}

		bool AABB2D::operator>=(const AABB2D& other) const
		{
			return (min > other.max);
		}

		bool AABB2D::operator<(const AABB2D& other) const
		{
			return (max < other.min);
		}

		bool AABB2D::operator>(const AABB2D& other) const
		{
			return (min > other.max);
		}

		// AABB3D -> 3D Vectors:

		AABB3D::AABB3D(const Vector3D& min, const Vector3D& max)
		{
			this->min.x = Maths::min<float>(min.x, max.x);
			this->min.y = Maths::min<float>(min.y, max.y);
			this->min.z = Maths::min<float>(min.z, max.z);

			this->max.x = Maths::max<float>(min.x, max.x);
			this->max.y = Maths::max<float>(min.y, max.y);
			this->max.z = Maths::max<float>(min.z, max.z);

			DELTAENGINE_ASSERT(this->min < this->max);
		}

		bool AABB3D::contains(const Vector3D& point) const
		{
			return (point >= min && point <= max);
		}

		bool AABB3D::intersects(const AABB3D& other) const
		{
			return (max > other.min && min < other.max); //|| (min > other.max && max < other.min);
		}

		const Vector3D AABB3D::getCenter() const
		{
			return min + (max - min) / 2.0f;
		}

		bool AABB3D::operator==(const AABB3D& other) const
		{
			return (min == other.min && max == other.max);
		}

		bool AABB3D::operator!=(const AABB3D& other) const
		{
			return !(*this == other);
		}

		bool AABB3D::operator<=(const AABB3D& other) const
		{
			return (max < other.min);
		}

		bool AABB3D::operator>=(const AABB3D& other) const
		{
			return (min > other.max);
		}

		bool AABB3D::operator<(const AABB3D& other) const
		{
			return (max < other.min);
		}

		bool AABB3D::operator>(const AABB3D& other) const
		{
			return (min > other.max);
		}

	}
}