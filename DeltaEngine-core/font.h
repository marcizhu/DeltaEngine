#pragma once

#include <string>
#include <FreeType-GL\freetype-gl.h>

#include "DeltaEngine.h"
#include "vector2d.h"

namespace DeltaEngine {
	namespace Graphics {

		class Font
		{
		private:
			ftgl::texture_atlas_t* atlas;
			ftgl::texture_font_t* font;
			Maths::Vector2D scale;
			std::string name;
			float size;
			//std::string filename;

		public:
			DELTAENGINE_API Font(std::string name, std::string filename, float size);

			DELTAENGINE_API inline ftgl::texture_font_t* getFTFont() const { return font; }

			DELTAENGINE_API inline const unsigned int getID() const { return atlas->id; }
			DELTAENGINE_API inline const std::string& getName() const { return name; }
			//DELTAENGINE_API inline const std::string& getFileName() const { return filename; }
			DELTAENGINE_API inline const float getSize() const { return size; }
			DELTAENGINE_API inline void getScale(float& x, float& y) const { x = scale.x; y = scale.y; }
			DELTAENGINE_API inline const Maths::Vector2D& getScale() const { return scale; }

			DELTAENGINE_API void setScale(float x, float y) { this->scale = Maths::Vector2D(x, y); }
			DELTAENGINE_API void setScale(Maths::Vector2D scale) { this->scale = scale; }
		};

	}
}
