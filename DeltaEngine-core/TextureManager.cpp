#include "textureManager.h"

namespace DeltaEngine {
	namespace Graphics {

		std::vector<Texture*> TextureManager::textures;

		Texture* TextureManager::get(const std::string& name)
		{
			for (Texture* texture : textures)
				if (texture->getName() == name) return texture;

			return nullptr;
		}

		void TextureManager::clean()
		{
			for (Types::uint32 i = 0; i < textures.size(); i++)
				delete textures[i];
		}

	}
}