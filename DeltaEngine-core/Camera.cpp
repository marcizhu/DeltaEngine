#include "camera.h"
#include "renderable2d.h"

namespace DeltaEngine {
	namespace Graphics {

		void Camera::setRelativePosition(float dx, float dy)
		{
			posX += dx;
			posY += dy;

			matrix.elements[0 + 0 * 4] = 2.0f / sizeX;
			matrix.elements[1 + 1 * 4] = 2.0f / -sizeY;

			matrix.elements[0 + 3 * 4] = (posX + (sizeX + posX)) / (posX - (sizeX + posX));
			matrix.elements[1 + 3 * 4] = ((sizeY + posY) + posY) / ((sizeY + posY) - posY);
		}
		
		void Camera::setAbsolutePosition(float x, float y)
		{
			posX = x;
			posY = y;

			matrix.elements[0 + 0 * 4] = 2.0f / sizeX;
			matrix.elements[1 + 1 * 4] = 2.0f / -sizeY;

			matrix.elements[0 + 3 * 4] = (posX + (sizeX + posX)) / (posX - (sizeX + posX));
			matrix.elements[1 + 3 * 4] = ((sizeY + posY) + posY) / ((sizeY + posY) - posY);
		}


		Camera::Camera(float left, float right, float top, float bottom, float near, float far)
			: posX(0), posY(0)
		{
			right -= left;
			bottom -= top;

			left = top = 0;

			this->sizeX = right;
			this->sizeY = bottom;

			matrix = Maths::Matrix4::orthographic(left, right, top, bottom, near, far);
			
			matrix.elements[2 + 2 * 4] = 2.0f / (near - far);
			matrix.elements[2 + 3 * 4] = (far + near) / (far - near);
		}

		void Camera::track(const Renderable2D& object, float left, float top)
		{
			float x = posX, y = posY;

			if (object.getFirstPosition().x - (this->sizeX / 2) >= left)
			{
				x = object.getFirstPosition().x - (this->sizeX / 2) - left;
			}

			if (object.getFirstPosition().y - (this->sizeY / 2) <= top)
			{
				y = object.getFirstPosition().y - (this->sizeY / 2) - top;
			}

			setAbsolutePosition(x, y);
		}

	}
}