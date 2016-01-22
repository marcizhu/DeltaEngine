#pragma once

#include <vector>

#include "DeltaEngine.h"
#include "texture.h"
#include "types.h"

using namespace DeltaEngine::Types;

namespace DeltaEngine {
	namespace Graphics {

		class Sprite {
		private:
			std::vector<Texture*> textures;
			uint32 currentTexture;

		public:
			Sprite() : currentTexture(0) { };

			void add(Texture* texture) { textures.push_back(texture); };

			void next() { currentTexture++; if (currentTexture >= textures.size()) currentTexture = 0; };
			void prev() { if (currentTexture == 0) { currentTexture = textures.size() - 1; } else { currentTexture--; } };
			void setCurrentTexture(uchar8 n) { currentTexture = n; };

			const Texture* getCurrentTexture() const { return textures[currentTexture]; };
			const uint32 getTextureCount() const { return textures.size(); };
		};

	}
}