#include "label.h"

namespace DeltaEngine {
	namespace Graphics {

		Label::Label(std::string text, float x, float y, Types::Color color)
			: Renderable2D(), text(text), x(x), y(y)
		{
			this->position = Maths::Vector2D(x, y);
			this->color = color.getABGRColor();
		}

		Label::Label(std::string text, float x, float y, Types::uint32 color)
			: Renderable2D(), text(text), x(x), y(y)
		{
			this->position = Maths::Vector2D(x, y);
			this->color = color;
		}

	}
}
