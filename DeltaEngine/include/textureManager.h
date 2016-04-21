#pragma once

#include <vector>

#include "internal.h"
#include "texture.h"

namespace DeltaEngine {
	namespace Graphics {

		class TextureManager
		{
		private:
			static std::vector<Texture*> textures;

		public:
			DELTAENGINE_API ~TextureManager() { clean(); };
			DELTAENGINE_API static void add(Texture* texture) { textures.push_back(texture); };
			DELTAENGINE_API static Texture* get(const std::string& name);
			DELTAENGINE_API static void clean();
		};

	}
}