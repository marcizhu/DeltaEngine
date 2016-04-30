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

		AABB::AABB(const Vector3D& min, const Vector3D& max)
		{
			this->min.x = Maths::min<float>(min.x, max.x);
			this->min.y = Maths::min<float>(min.y, max.y);
			this->min.z = Maths::min<float>(min.z, max.z);

			this->max.x = Maths::max<float>(min.x, max.x);
			this->max.y = Maths::max<float>(min.y, max.y);
			this->max.z = Maths::max<float>(min.z, max.z);

			DELTAENGINE_ASSERT(this->min < this->max);
		}

		AABB::AABB(const Vector2D& min, const Vector2D& max)
		{
			this->min.x = Maths::min<float>(min.x, max.x);
			this->min.y = Maths::min<float>(min.y, max.y);
			this->min.z = 0.0f;

			this->max.x = Maths::max<float>(min.x, max.x);
			this->max.y = Maths::max<float>(min.y, max.y);
			this->max.z = 0.0f;

			DELTAENGINE_ASSERT(this->min <= this->max); // We need the '=' because min.z == max.z
		}

		bool AABB::contains(const Vector3D& point) const
		{
			return (point >= min && point <= max);
		}

		bool AABB::contains(const Vector2D& point) const
		{
			return (point.x >= min.x && point.y >= min.y && point.x <= max.x && point.y <= max.y);
		}

		bool AABB::intersects(const AABB& other) const
		{
			return (max > other.min && min < other.max); //|| (min > other.max && max < other.min);
		}

		const Vector3D AABB::getCenter() const
		{
			return min + (max - min) / 2.0f;
		}

		bool AABB::operator==(const AABB& other) const
		{
			return (min == other.min && max == other.max);
		}

		bool AABB::operator!=(const AABB& other) const
		{
			return !(*this == other);
		}

		bool AABB::operator<=(const AABB& other) const
		{
			return (max < other.min);
		}

		bool AABB::operator>=(const AABB& other) const
		{
			return (min > other.max);
		}

		bool AABB::operator<(const AABB& other) const
		{
			return (max < other.min);
		}

		bool AABB::operator>(const AABB& other) const
		{
			return (min > other.max);
		}

	}
}