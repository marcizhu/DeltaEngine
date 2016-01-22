#pragma once

#include <GLEW/glew.h>
#include <FreeImage\FreeImage.h>
#include <string>

#include "DeltaEngine.h"
#include "types.h"

using namespace DeltaEngine::Types;

namespace DeltaEngine {
	namespace Graphics {

		class Texture
		{
		private:
			std::string textureName;
			GLuint textureID;
			uint32 width, height;
			uchar8 bpp;

			BYTE* loadImage(const char* filename, uint32* width, uint32* height, uchar8* bpp);

		public:
			DELTAENGINE_API Texture(const std::string& name, const std::string& filename, uint32 texParam = GL_LINEAR);
			DELTAENGINE_API ~Texture() { glDeleteTextures(1, &textureID); };

			DELTAENGINE_API inline void bind() const { glBindTexture(GL_TEXTURE_2D, textureID); };
			DELTAENGINE_API inline void unbind() const { glBindTexture(GL_TEXTURE_2D, 0); };

			DELTAENGINE_API inline const uint32 getWidth() const { return width; }
			DELTAENGINE_API inline const uint32 getHeight() const { return height; }
			DELTAENGINE_API inline const uint32 getID() const { return textureID; }
			DELTAENGINE_API inline const uchar8 getBPP() const { return bpp; }
			DELTAENGINE_API inline const std::string& getName() const { return textureName; }
		};

	}
}