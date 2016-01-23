#include "label.h"
#include "fontManager.h"

namespace DeltaEngine {
	namespace Graphics {

		Label::Label(std::string text, float x, float y, Font* font, Types::Color color)
			: Renderable2D(), text(text), x(x), y(y), font(font)
		{
			this->position = Maths::Vector2D(x, y);
			this->color = color.getABGRColor();
		}

		Label::Label(std::string text, float x, float y, Font* font, Types::uint32 color)
			: Renderable2D(), text(text), x(x), y(y), font(font)
		{
			this->position = Maths::Vector2D(x, y);
			this->color = color;
		}

		Label::Label(std::string text, float x, float y, const std::string& font, Types::Color color)
			: Renderable2D(), text(text), x(x), y(y), font(FontManager::get(font))
		{
			this->position = Maths::Vector2D(x, y);
			this->color = color.getABGRColor();
		}

		Label::Label(std::string text, float x, float y, const std::string& font, Types::uint32 color)
			: Renderable2D(), text(text), x(x), y(y), font(FontManager::get(font))
		{
			this->position = Maths::Vector2D(x, y);
			this->color = color;
		}

		Label::Label(std::string text, float x, float y, const std::string& font, Types::uint32 size, Types::Color color)
			: Renderable2D(), text(text), x(x), y(y), font(FontManager::get(font, size))
		{
			this->position = Maths::Vector2D(x, y);
			this->color = color.getABGRColor();
		}

		Label::Label(std::string text, float x, float y, const std::string& font, Types::uint32 size, Types::uint32 color)
			: Renderable2D(), text(text), x(x), y(y), font(FontManager::get(font, size))
		{
			this->position = Maths::Vector2D(x, y);
			this->color = color;
		}

		void Label::setText(std::string& text)
		{
			this->text = text;
		}

	}
}
