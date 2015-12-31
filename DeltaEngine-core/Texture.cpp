#include "texture.h"

namespace DeltaEngine {
	namespace Graphics {

		Texture::Texture(const std::string& filename, uint32 texParam) : filename(filename)
		{
			BYTE* pixels = loadImage(filename.c_str(), &width, &height);

			glGenTextures(1, &textureID);
			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texParam);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texParam);

			switch (bpp)
			{
			case 24:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels); break;

			case 32:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels); break;

			default:
				std::cout << "Invalid bpp value: " << bpp << std::endl; break;
			}

			glBindTexture(GL_TEXTURE_2D, 0);
		}

		BYTE* Texture::loadImage(const char* filename, uint32* width, uint32* height)
		{
			FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
			FIBITMAP *dib = nullptr;

			fif = FreeImage_GetFileType(filename, 0);

			if (fif == FIF_UNKNOWN) fif = FreeImage_GetFIFFromFilename(filename);
			if (fif == FIF_UNKNOWN) return nullptr;

			if (FreeImage_FIFSupportsReading(fif)) dib = FreeImage_Load(fif, filename);
			
			if (!dib) return nullptr;

			BYTE* result = FreeImage_GetBits(dib);
			
			*width = FreeImage_GetWidth(dib);
			*height = FreeImage_GetHeight(dib);
			
			bpp = FreeImage_GetBPP(dib);

			return result;
		}

	}
}