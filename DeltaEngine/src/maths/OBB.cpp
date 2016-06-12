#include "obb.h"

namespace DeltaEngine {
	namespace Maths {

		OBB2D::OBB2D(Maths::Vector2D& center, float sizeX, float sizeY, float angle)
		{
			sizeX /= 2.0f;
			sizeY /= 2.0f;

			Maths::Matrix4 rotation = Maths::Matrix4::identity();

			rotation.translate(center.x, center.y, 0);
			rotation.rotate(angle, 0, 0, 1);

			this->vertex[0] = rotation * Maths::Vector2D(-sizeX, -sizeY);
			this->vertex[1] = rotation * Maths::Vector2D(-sizeX,  sizeY);
			this->vertex[2] = rotation * Maths::Vector2D( sizeX,  sizeY);
			this->vertex[3] = rotation * Maths::Vector2D( sizeX, -sizeY);

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

			minPoint = Maths::Vector2D(minX, minY);
			maxPoint = Maths::Vector2D(maxX, maxY);

			box = Maths::AABB(Maths::Vector2D(minX, minY), Maths::Vector2D(maxX, maxY));
		}

		OBB2D::OBB2D(Maths::Vector2D& center, Maths::Vector2D size, float angle)
		{
			size = size / 2.0f;

			Maths::Matrix4 rotation = Maths::Matrix4::identity();

			rotation.translate(center.x, center.y, 0);
			rotation.rotate(angle, 0, 0, 1);

			this->vertex[0] = rotation * Maths::Vector2D(-size.x, -size.y);
			this->vertex[1] = rotation * Maths::Vector2D(-size.x,  size.y);
			this->vertex[2] = rotation * Maths::Vector2D( size.x,  size.y);
			this->vertex[3] = rotation * Maths::Vector2D( size.x, -size.y);

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

			minPoint = Maths::Vector2D(minX, minY);
			maxPoint = Maths::Vector2D(maxX, maxY);

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
			const OBB2D* nearest;
			const OBB2D* farthest;

			if (other.getCenter().distance() < this->getCenter().distance())
			{
				nearest = &other;
				farthest = this;
			}
			else
			{
				nearest = this;
				farthest = &other;
			}

			if (nearest->getFarthestPoint().x <= farthest->getNearestPoint().x) return true;
			if (nearest->getFarthestPoint().y >= farthest->getNearestPoint().y) return true;

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