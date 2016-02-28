#include "texture.h"
#include "log.h"

namespace DeltaEngine {
	namespace Graphics {

		std::map<std::string, Texture*> Texture::textureCache;

		Texture::Texture(const std::string& name, const std::string& filename, Types::uint32 texParam)
			: textureName(name)
		{
			auto& result = textureCache.find(filename);

			if (result != textureCache.end())
			{
				DELTAENGINE_INFO("[Texture] Loading texture \'", filename, "\' from cache");

				this->bpp = textureCache[filename]->bpp;
				this->height = textureCache[filename]->height;
				this->textureID = textureCache[filename]->textureID;
				this->width = textureCache[filename]->width;
			}
			else
			{
				DELTAENGINE_INFO("[Texture] Caching texture \'", filename, "\'");

				BYTE* pixels = loadImage(filename.c_str(), &width, &height, &bpp);

				if (pixels == nullptr)
				{
					DELTAENGINE_ERROR("[Texture] Unable to read the texture file '", filename, "'!");
					return;
				}

				glGenTextures(1, &textureID);
				glBindTexture(GL_TEXTURE_2D, textureID);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texParam);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texParam);

				switch (bpp)
				{
				case 24:
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels); break;

				case 32:
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels);
					glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); break;

				default:
					DELTAENGINE_WARN("[Texture] Invalid bpp value: ", bpp); break;
				}

				glBindTexture(GL_TEXTURE_2D, 0);

				delete[] pixels;

				textureCache[filename] = this;
			}
		}

		BYTE* Texture::loadImage(const char* filename, Types::uint32* width, Types::uint32* height, Types::uchar8* bpp)
		{
			FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
			FIBITMAP *dib = nullptr;
			
			fif = FreeImage_GetFileType(filename, 0);

			if (fif == FIF_UNKNOWN)
			{
				fif = FreeImage_GetFIFFromFilename(filename);
				if (fif == FIF_UNKNOWN) return nullptr;
			}

			if (FreeImage_FIFSupportsReading(fif)) dib = FreeImage_Load(fif, filename);

			if (!dib) return nullptr;

			BYTE* pixels = FreeImage_GetBits(dib);

			*width = FreeImage_GetWidth(dib);
			*height = FreeImage_GetHeight(dib);
			*bpp = FreeImage_GetBPP(dib);

			Types::uint32 size = *width * *height * (*bpp / 8);

			BYTE* result = new BYTE[size];
			memcpy(result, pixels, size);

			FreeImage_Unload(dib);

			return result;
		}

	}
}