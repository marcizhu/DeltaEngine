#pragma once

#include <GLEW\glew.h>
#include <FreeImage\FreeImage.h>
#include <string>

#include "DeltaEngine.h"
#include "types.h"

//using namespace DeltaEngine::Types;

namespace DeltaEngine {
	namespace Graphics {

		class Texture
		{
		private:
			std::string textureName;
			GLuint textureID;
			Types::uint32 width, height;
			Types::uchar8 bpp;

			BYTE* loadImage(const char* filename, Types::uint32* width, Types::uint32* height, Types::uchar8* bpp);

		public:
			DELTAENGINE_API Texture(const std::string& name, const std::string& filename, Types::uint32 texParam = GL_LINEAR);
			DELTAENGINE_API ~Texture() { glDeleteTextures(1, &textureID); };

			DELTAENGINE_API inline void bind() const { glBindTexture(GL_TEXTURE_2D, textureID); };
			DELTAENGINE_API inline void unbind() const { glBindTexture(GL_TEXTURE_2D, 0); };

			DELTAENGINE_API inline const Types::uint32 getWidth() const { return width; }
			DELTAENGINE_API inline const Types::uint32 getHeight() const { return height; }
			DELTAENGINE_API inline const Types::uint32 getID() const { return textureID; }
			DELTAENGINE_API inline const Types::uchar8 getBPP() const { return bpp; }
			DELTAENGINE_API inline const std::string& getName() const { return textureName; }
		};

	}
}