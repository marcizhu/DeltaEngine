#pragma once

#include <string>
#include <FreeType-GL\freetype-gl.h>

#include "DeltaEngine.h"

namespace DeltaEngine {
	namespace Graphics {

		class Font
		{
		private:
			ftgl::texture_atlas_t* atlas;
			ftgl::texture_font_t* font;
			unsigned int size;

			std::string name;
			std::string filename;

		public:
			DELTAENGINE_API Font(std::string name, std::string filename, int size);

			DELTAENGINE_API inline ftgl::texture_font_t* getFTFont() const { return font; }

			DELTAENGINE_API inline const unsigned int getID() const { return atlas->id; }
			DELTAENGINE_API inline const std::string& getName() const { return name; }
			DELTAENGINE_API inline const std::string& getFileName() const { return filename; }
			DELTAENGINE_API inline const int getSize() const { return size; }
		};

	}
}
