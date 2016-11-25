#include "obb.h"

namespace DeltaEngine {
	namespace Maths {

		Maths::Vector2D OBB2D::rotateVector(Maths::Vector2D& center, Maths::Vector2D& point, float degrees)
		{
			Maths::Vector2D ret;

			degrees = Maths::toRadians(degrees);

			ret.x = center.x + point.x * cos(degrees) - point.y * sin(degrees);
			ret.y = center.y + point.x * sin(degrees) + point.y * cos(degrees);

			return ret;
		}

		OBB2D::OBB2D(Maths::Vector2D& center, float sizeX, float sizeY, float angle)
		{
			sizeX /= 2.0f;
			sizeY /= 2.0f;

			this->vertex[0] = rotateVector(center, Maths::Vector2D(-sizeX, -sizeY), angle);
			this->vertex[1] = rotateVector(center, Maths::Vector2D(-sizeX,  sizeY), angle);
			this->vertex[2] = rotateVector(center, Maths::Vector2D( sizeX,  sizeY), angle);
			this->vertex[3] = rotateVector(center, Maths::Vector2D( sizeX, -sizeY), angle);
		}

		OBB2D::OBB2D(Maths::Vector2D& center, Maths::Vector2D size, float angle)
		{
			size = size / 2.0f;

			this->vertex[0] = rotateVector(center, Maths::Vector2D(-size.x, -size.y), angle);
			this->vertex[1] = rotateVector(center, Maths::Vector2D(-size.x,  size.y), angle);
			this->vertex[2] = rotateVector(center, size, angle);
			this->vertex[3] = rotateVector(center, Maths::Vector2D( size.x, -size.y), angle);
		}

		bool OBB2D::contains(Maths::Vector2D& point) const
		{
			// TODO: Check if the dot is inside the OBB

			return true;
		}

		bool OBB2D::intersects(Maths::OBB2D& other) const
		{
			// TODO: Check if another OBB intersects this one

			return true;
		}

		const Vector2D OBB2D::getCenter() const
		{
			float ymax = max(max(vertex[0].y, vertex[1].y), max(vertex[2].y, vertex[3].y));
			float ymin = min(min(vertex[0].y, vertex[1].y), min(vertex[2].y, vertex[3].y));
			float y = (ymax + ymin) / 2.0f;

			float xmax = max(max(vertex[0].x, vertex[1].x), max(vertex[2].x, vertex[3].x));
			float xmin = min(min(vertex[0].x, vertex[1].x), min(vertex[2].x, vertex[3].x));
			float x = (xmax + xmin) / 2.0f;

			return Maths::Vector2D(x, y);
		}

		void OBB2D::moveTo(Maths::Vector2D& point)
		{
			Maths::Vector2D delta = point - this->getCenter();

			for (unsigned int i = 0; i < 4; i++)
			{
				vertex[i] += delta;
			}
		}

	}
}