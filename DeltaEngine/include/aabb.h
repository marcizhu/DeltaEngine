#pragma once

#include "internal.h"
#include "maths.h"
#include "vector2d.h"
#include "vector3d.h"
#include "vector4d.h"

#if defined(min) || defined(max)
#	undef min
#	undef max
#endif

namespace DeltaEngine {
	namespace Maths {

		class AABB
		{
		private:
			Vector3D min;
			Vector3D max;

		public:
			DELTAENGINE_API inline AABB() : min(), max() {}
			DELTAENGINE_API AABB(const Vector2D& min, const Vector2D& max);
			DELTAENGINE_API AABB(const Vector3D& min, const Vector3D& max);

			DELTAENGINE_API bool contains(const Vector2D& point) const;
			DELTAENGINE_API bool contains(const Vector3D& point) const;
			DELTAENGINE_API bool intersects(const AABB& other) const;
			DELTAENGINE_API inline const Vector3D getCenter() const;

			DELTAENGINE_API inline bool operator==(const AABB& other) const;
			DELTAENGINE_API inline bool operator!=(const AABB& other) const;
			DELTAENGINE_API inline bool operator<=(const AABB& other) const;
			DELTAENGINE_API inline bool operator>=(const AABB& other) const;
			DELTAENGINE_API inline bool operator<(const AABB& other) const;
			DELTAENGINE_API inline bool operator>(const AABB& other) const;
		};

	}
}