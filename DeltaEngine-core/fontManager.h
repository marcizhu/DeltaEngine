#pragma once

#include <vector>

#include "DeltaEngine.h"
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
		};

	}
}
