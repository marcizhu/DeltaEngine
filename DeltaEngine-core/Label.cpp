#include "label.h"

namespace DeltaEngine {
	namespace Graphics {

		Label::Label(std::string text, float x, float y, Types::Color color)
			: Renderable2D(), text(text), position(Maths::Vector2D(x, y))
		{
			//position = Maths::Vector2D(x, y);
			this->color = color;
		}

	}
}
