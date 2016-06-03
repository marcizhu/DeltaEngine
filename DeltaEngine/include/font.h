#pragma once

#include <string>
#include <FreeType-GL\freetype-gl.h>

#include "internal.h"
#include "vector2d.h"
#include "types.h"
#include "texture.h"

namespace DeltaEngine {
	namespace Graphics {

		class Font
		{
		private:
			ftgl::texture_font_t* font;
			ftgl::texture_atlas_t* atlas;
			Maths::Vector2D scale;
			std::string name;
			Texture* texture;
			float size;

		public:
			DELTAENGINE_API Font(const std::string& name, const std::string& filename, float size);
			DELTAENGINE_API Font(const std::string& name, const Types::byte* data, Types::uint32 dataSize, float size);
			DELTAENGINE_API ~Font();

			DELTAENGINE_API inline ftgl::texture_font_t* getFTFont() const { return font; }

			DELTAENGINE_API inline const float getSize() const { return size; }
			DELTAENGINE_API inline const unsigned int getID() const { return atlas->id; }
			DELTAENGINE_API inline const std::string& getName() const { return name; }
			DELTAENGINE_API inline const Maths::Vector2D& getScale() const { return scale; }
			DELTAENGINE_API inline void getScale(float& x, float& y) const { x = scale.x; y = scale.y; }

			DELTAENGINE_API void setScale(float x, float y) { this->scale = Maths::Vector2D(x, y); }
			DELTAENGINE_API void setScale(Maths::Vector2D scale) { this->scale = scale; }

			DELTAENGINE_API inline Texture* getTexture() const { texture->setData(atlas->data); return texture; }
		};

	}
}
