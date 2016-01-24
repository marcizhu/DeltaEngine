#include "font.h"

namespace DeltaEngine {
	namespace Graphics {
		
		Font::Font(std::string name, std::string filename, float size) 
			: name(name), size(size)
		{
			atlas = ftgl::texture_atlas_new(512, 512, 2);
			font = ftgl::texture_font_new_from_file(atlas, size, filename.c_str());
		}

	}
}
