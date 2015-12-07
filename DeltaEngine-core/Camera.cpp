#include "camera.h"
#include "renderable2d.h"

namespace DeltaEngine {
	namespace Graphics {
		
		void Camera::setPosition(float dx, float dy, bool absolute)
		{
			absolute ? posX = dx : posX += dx;
			absolute ? posY = dy : posY += dy;
			
			matrix.elements[0 + 0 * 4] = 2.0f / sizeX;
			matrix.elements[1 + 1 * 4] = 2.0f / -sizeY;

			matrix.elements[0 + 3 * 4] = (2 * posX + sizeX) / -sizeX;
			matrix.elements[1 + 3 * 4] = (sizeY + 2 * posY) / sizeY;
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
			float x, y;

			posY < 0.0f ? y = 0.0f : y = posY;
			posX > 0.0f ? x = 0.0f : x = posX;

			if (object.getFirstPosition().x >= left) x = object.getFirstPosition().x - left;
			if (object.getFirstPosition().y <= top) y = object.getFirstPosition().y - top;

			setPosition(x, y, true);
		}

	}
}