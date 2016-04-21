#pragma once

#include <vector>

#include "internal.h"
#include "font.h"

namespace DeltaEngine {
	namespace Graphics {

		class FontManager
		{
		private:
			static std::vector<Font*> fonts;

		public:
			DELTAENGINE_API ~FontManager() { clean(); };
			DELTAENGINE_API static void add(Font* font);
			DELTAENGINE_API static Font* get(const std::string& name);
			DELTAENGINE_API static Font* get(const std::string& name, unsigned int size);
			DELTAENGINE_API static void clean();

			DELTAENGINE_API static void setScale(float x, float y);
			DELTAENGINE_API static void setScale(Maths::Vector2D& scale);
		};

	}
}
