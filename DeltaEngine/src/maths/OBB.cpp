#include "obb.h"

namespace DeltaEngine {
	namespace Maths {

		OBB2D::OBB2D(Maths::Vector2D& center, float sizeX, float sizeY, float angle)
		{
			angle = fmodf(angle, 90.0f);

			sizeX /= 2.0f;
			sizeY /= 2.0f;

			float cosine = cos(Maths::toRadians(angle));
			float sine = sin(Maths::toRadians(angle));

			this->vertex[0].x = center.x - sizeX * cosine - sizeY * sine;
			this->vertex[0].y = center.y + sizeX * sine	- sizeY * cosine;

			this->vertex[1].x = center.x - sizeX * cosine - sizeY * sine;
			this->vertex[1].y = center.y + sizeX * sine + sizeY * cosine;

			this->vertex[2].x = center.x + sizeX * cosine - sizeY * sine;
			this->vertex[2].y = center.y + sizeX * sine + sizeY * cosine;

			this->vertex[3].x = center.x + sizeX * cosine - sizeY * sine;
			this->vertex[3].y = center.y + sizeX * sine - sizeY * cosine;

			float minX, maxX;
			float minY, maxY;

			minX = maxX = center.x;
			minY = maxY = center.y;

			for (unsigned int i = 0; i < 4; i++)
			{
				if (vertex[i].x < minX) minX = vertex[i].x;
				if (vertex[i].x > maxX) maxX = vertex[i].x;

				if (vertex[i].y < minY) minY = vertex[i].y;
				if (vertex[i].y > maxY) maxY = vertex[i].y;
			}

			box = Maths::AABB(Maths::Vector2D(minX, minY), Maths::Vector2D(maxX, maxY));
		}

		OBB2D::OBB2D(Maths::Vector2D& center, Maths::Vector2D size, float angle)
		{
			angle = fmodf(angle, 90.0f);

			size = size / 2.0f;

			float cosine = cos(Maths::toRadians(angle));
			float sine = sin(Maths::toRadians(angle));

			this->vertex[0].x = center.x - size.x * cosine - size.y * sine;
			this->vertex[0].y = center.y + size.x * sine - size.y * cosine;

			this->vertex[1].x = center.x - size.x * cosine - size.y * sine;
			this->vertex[1].y = center.y + size.x * sine + size.y * cosine;

			this->vertex[2].x = center.x + size.x * cosine - size.y * sine;
			this->vertex[2].y = center.y + size.x * sine + size.y * cosine;

			this->vertex[3].x = center.x + size.x * cosine - size.y * sine;
			this->vertex[3].y = center.y + size.x * sine - size.y * cosine;

			float minX, maxX;
			float minY, maxY;

			minX = maxX = center.x;
			minY = maxY = center.y;

			for (unsigned int i = 0; i < 4; i++)
			{
				if (vertex[i].x < minX) minX = vertex[i].x;
				if (vertex[i].x > maxX) maxX = vertex[i].x;

				if (vertex[i].y < minY) minY = vertex[i].y;
				if (vertex[i].y > maxY) maxY = vertex[i].y;
			}

			box = Maths::AABB(Maths::Vector2D(minX, minY), Maths::Vector2D(maxX, maxY));
		}

		bool OBB2D::contains(Maths::Vector2D& point) const
		{
			if (!box.contains(point)) return false;

			// TODO: Check if the dot is inside the OBB

			return true;
		}

		bool OBB2D::intersects(Maths::OBB2D& other) const
		{
			return false;
		}

		const Vector2D OBB2D::getCenter() const
		{
			return Maths::Vector2D(box.getCenter().x, box.getCenter().y);
		}

		void OBB2D::moveTo(Maths::Vector2D& point)
		{
			Maths::Vector2D delta = point - getCenter();

			for (unsigned int i = 0; i < 4; i++)
			{
				vertex[i] += delta;
			}

			box += delta;
		}

	}
}