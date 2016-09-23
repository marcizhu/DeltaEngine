#include "obb.h"

// Rotation: http://stackoverflow.com/questions/12161277/how-to-rotate-a-vertex-around-a-certain-point

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
			// TODO: Calculate the center

			return Maths::Vector2D(); //minPoint + (maxPoint - minPoint) / 2.0f;
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