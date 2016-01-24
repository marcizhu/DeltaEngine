#pragma once

#include <string>

#include "DeltaEngine.h"
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
			//TODO: Remove this! Use Renderable2D::position instead
			//float x, y;

		public:
			DELTAENGINE_API Label(std::string text, float x, float y, Font* font, Types::Color color);
			DELTAENGINE_API Label(std::string text, float x, float y, Font* font, Types::uint32 color);
			DELTAENGINE_API Label(std::string text, float x, float y, const std::string& font, Types::Color color);
			DELTAENGINE_API Label(std::string text, float x, float y, const std::string& font, Types::uint32 color);
			DELTAENGINE_API Label(std::string text, float x, float y, const std::string& font, Types::uint32 size, Types::Color color);
			DELTAENGINE_API Label(std::string text, float x, float y, const std::string& font, Types::uint32 size, Types::uint32 color);
			
			DELTAENGINE_API void submit(Renderer2D* renderer) const override { renderer->drawString(text, position, *font, color); };
			DELTAENGINE_API void setText(std::string& text);
			DELTAENGINE_API const std::string& getText() const { return text; };
		};

	}
}