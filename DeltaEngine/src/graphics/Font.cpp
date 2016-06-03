#include <FreeType-GL\texture-font.h>
#include <FreeImage\FreeImage.h>
#include <string>

#include "font.h"
#include "types.h"
#include "memoryManager.h"

namespace DeltaEngine {
	namespace Graphics {

		Font::Font(const std::string& name, const std::string& filename, float size)
			: name(name), size(size)
		{
			atlas = ftgl::texture_atlas_new(512, 512, 2);
			font = ftgl::texture_font_new_from_file(atlas, size, filename.c_str());

			texture = NEW Texture(512, 512, 2);
			texture->setData(atlas->data);
		}

		Font::Font(const std::string& name, const Types::byte* data, Types::uint32 dataSize, float size)
			: name(name), size(size)
		{
			atlas = ftgl::texture_atlas_new(512, 512, 2);
			font = ftgl::texture_font_new_from_memory(atlas, size, data, dataSize);

			texture = NEW Texture(512, 512, 2);
			texture->setData(atlas->data);
		}

		Font::~Font()
		{
			ftgl::texture_atlas_delete(atlas);
			ftgl::texture_font_delete(font);

			delete texture;
		}
	}
}
