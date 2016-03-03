#include "label.h"
#include "fontManager.h"

namespace DeltaEngine {
	namespace Graphics {

		Label::Label(std::string text, float x, float y, Font* font, Types::Color color)
			: Renderable2D(), text(text), font(font)
		{
			this->position = Maths::Vector2D(x, y);
			this->color = color.getABGRColor();
		}

		Label::Label(std::string text, float x, float y, Font* font, Types::uint32 color)
			: Renderable2D(), text(text), font(font)
		{
			this->position = Maths::Vector2D(x, y);
			this->color = color;
		}

		Label::Label(std::string text, float x, float y, const std::string& font, Types::Color color)
			: Renderable2D(), text(text), font(FontManager::get(font))
		{
			this->position = Maths::Vector2D(x, y);
			this->color = color.getABGRColor();
		}

		Label::Label(std::string text, float x, float y, const std::string& font, Types::uint32 color)
			: Renderable2D(), text(text), font(FontManager::get(font))
		{
			this->position = Maths::Vector2D(x, y);
			this->color = color;
		}

		Label::Label(std::string text, float x, float y, const std::string& font, Types::uint32 size, Types::Color color)
			: Renderable2D(), text(text), font(FontManager::get(font, size))
		{
			this->position = Maths::Vector2D(x, y);
			this->color = color.getABGRColor();
		}

		Label::Label(std::string text, float x, float y, const std::string& font, Types::uint32 size, Types::uint32 color)
			: Renderable2D(), text(text), font(FontManager::get(font, size))
		{
			this->position = Maths::Vector2D(x, y);
			this->color = color;
		}

		void Label::setText(std::string& text)
		{
			this->text = text;
		}

#define MAX(a, b) a > b ? a : b

		const Maths::Vector2D Label::getSize(const Font& font)
		{
			const Maths::Vector2D& scale = font.getScale();

			float x = 0.0f;
			float maxX = 0.0f;
			float y = 0.0f;

			for (Types::uint32 i = 0; i < text.length(); i++)
			{
				char c = text[i];
				texture_glyph_t* glyph = texture_font_get_glyph(font.getFTFont(), &c);

				if (glyph)
				{
					if (i > 0)
					{
						float kerning = texture_glyph_get_kerning(glyph, &text[i - 1]);
						x += kerning / scale.x;
					}

					if (c == '\n')
					{
						y += (glyph->advance_y > 0.0f ? glyph->advance_y : (glyph->height + (font.getSize() + 6) / 3)) / scale.y;
						maxX = MAX(maxX, x);
						x = 0.0f;
						continue;
					}

					x += glyph->advance_x / scale.x;
				}
			}

			this->size = Maths::Vector2D(maxX, y);

			return this->size;
		}

	}
}
