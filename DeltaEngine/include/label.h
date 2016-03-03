#pragma once

#include <string>

#include "internal.h"
#include "renderable2d.h"
#include "renderer2d.h"
#include "types.h"
#include "font.h"

namespace DeltaEngine {
	namespace Graphics {

		class Label : public Renderable2D
		{
		public:
			std::string text;
			Font* font;

		public:
			DELTAENGINE_API Label(std::string text, float x, float y, Font* font, Types::Color color);
			DELTAENGINE_API Label(std::string text, float x, float y, Font* font, Types::uint32 color);
			DELTAENGINE_API Label(std::string text, float x, float y, const std::string& font, Types::Color color);
			DELTAENGINE_API Label(std::string text, float x, float y, const std::string& font, Types::uint32 color);
			DELTAENGINE_API Label(std::string text, float x, float y, const std::string& font, Types::uint32 size, Types::Color color);
			DELTAENGINE_API Label(std::string text, float x, float y, const std::string& font, Types::uint32 size, Types::uint32 color);

			DELTAENGINE_API void submit(Renderer2D* renderer) const override { renderer->drawString(text, position, *font, color); };

			DELTAENGINE_API inline void setText(std::string& text);

			DELTAENGINE_API inline const std::string& getText() const { return text; };
			DELTAENGINE_API const Maths::Vector2D getSize(const Font& font);
		};

	}
}