#include <vector>

#include "fontManager.h"
#include "types.h"
#include "memoryManager.h"

namespace DeltaEngine {
	namespace Graphics {

		std::vector<Font*> FontManager::fonts;

		void FontManager::add(Font* font)
		{
			fonts.push_back(font);
		}

		Font* FontManager::get(const std::string& name)
		{
			for (Font* font : fonts)
				if (font->getName() == name) return font;

			return nullptr;
		}

		Font* FontManager::get(const std::string& name, unsigned int size)
		{
			for (Font* font : fonts)
				if (font->getSize() == size && font->getName() == name) return font;

			return nullptr;
		}

		void FontManager::clean()
		{
			for (Types::uint32 i = 0; i < fonts.size(); i++)
				delete fonts[i];
		}

	}
}
