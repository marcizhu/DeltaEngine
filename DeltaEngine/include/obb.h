#pragma once

#include "internal.h"
#include "vector2d.h"
#include "aabb.h"

namespace DeltaEngine {
	namespace Maths {

		class OBB2D
		{
		private:
			Maths::Vector2D vertex[4];
			Maths::AABB box;

		public:
			DELTAENGINE_API OBB2D() : vertex(), box() {};
			DELTAENGINE_API OBB2D(Maths::Vector2D& center, float sizeX, float sizeY, float angle);
			DELTAENGINE_API OBB2D(Maths::Vector2D& center, Maths::Vector2D size, float angle);

			DELTAENGINE_API bool intersects(Maths::OBB2D& other) const;
			DELTAENGINE_API bool contains(Maths::Vector2D& point) const;

			DELTAENGINE_API void moveTo(Maths::Vector2D& point);

			DELTAENGINE_API inline const Vector2D getCenter() const;

			/*
			DELTAENGINE_API inline bool operator==(const AABB& other) const;
			DELTAENGINE_API inline bool operator!=(const AABB& other) const;
			DELTAENGINE_API inline bool operator<=(const AABB& other) const;
			DELTAENGINE_API inline bool operator>=(const AABB& other) const;
			DELTAENGINE_API inline bool operator<(const AABB& other) const;
			DELTAENGINE_API inline bool operator>(const AABB& other) const;
			*/
		};

	}
}