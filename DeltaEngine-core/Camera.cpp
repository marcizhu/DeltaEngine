#include "renderable2d.h"
#include "maths.h"
#include "camera.h"

namespace DeltaEngine {
	namespace Graphics {
		
		void Camera::setPosition(float dx, float dy, bool absolute)
		{
			absolute ? posX = dx : posX += dx;
			absolute ? posY = dy : posY += dy;
			
			matrix.elements[0 + 0 * 4] = 2.0f / sizeX;
			matrix.elements[1 + 1 * 4] = 2.0f / -sizeY;

			matrix.elements[0 + 3 * 4] = (2 * posX + sizeX) / (hFlip ? sizeX : -sizeX);
			matrix.elements[1 + 3 * 4] = (sizeY + 2 * posY) / (vFlip ? -sizeY : sizeY);
		}
		
		Camera::Camera(float left, float right, float top, float bottom, float near, float far)
		{
			right -= left;
			bottom -= top;

			left = top = 0;

			this->sizeX = right;
			this->sizeY = bottom;

			matrix = Maths::Matrix4::orthographic(left, right, top, bottom, near, far);
			
			matrix.elements[2 + 2 * 4] = 2.0f / (near - far);
			matrix.elements[2 + 3 * 4] = (far + near) / (far - near);

			hFlip = right < 0.0f ? true : false;
			vFlip = bottom < 0.0f ? true : false;

			setPosition(0.0f, 0.0f, true);
		}

		//TODO: Optimize this!
		/*void Camera::track(const Renderable2D& object, float left, float top)
		{
			float x, y;

			posY < 0.0f ? y = 0.0f : y = posY;
			posX > 0.0f ? x = 0.0f : x = posX;

			if (hFlip)
			{
				if (object.getFirstPosition().x <= left) x = left - object.getFirstPosition().x;
			} else
			{
				if (object.getFirstPosition().x >= left) x = object.getFirstPosition().x - left;
			}

			if (vFlip)
			{
				if (object.getFirstPosition().y >= top) y =  top - object.getFirstPosition().y;
			} else
			{
				if (object.getFirstPosition().y <= top) y = object.getFirstPosition().y - top;
			}

			setPosition(x, y, true);
		}*/

	}
}