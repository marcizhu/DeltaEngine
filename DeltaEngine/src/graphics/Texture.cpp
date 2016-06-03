#include <FreeImage\FreeImage.h>

#include "texture.h"
#include "log.h"
#include "memoryManager.h"

namespace DeltaEngine {
	namespace Graphics {

		Texture::Texture(uint32 width, uint32 height, uchar8 bpp) : width(width), height(height), bpp(bpp)
		{
			glGenTextures(1, &textureID);

			glBindTexture(GL_TEXTURE_2D, textureID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);

			switch (bpp)
			{
			case 2:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, NULL); break;

			case 24:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, NULL); break;

			case 32:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL); break;

			default:
				DELTAENGINE_WARN("[Texture] Invalid bpp value: ", bpp); break;
			}
		}

		Texture::Texture(const std::string& name, const std::string& filename, Types::uint32 texParam) : textureName(name)
		{
			Types::byte* pixels = loadImage(filename.c_str(), &width, &height, &bpp);

			if (pixels == nullptr)
			{
				DELTAENGINE_ERROR("[Texture] Unable to read the texture file '", filename, "'!");
				return;
			}

			glGenTextures(1, &textureID);
			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texParam == GL_NEAREST ? GL_NEAREST_MIPMAP_NEAREST : GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texParam);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

			glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

			switch (bpp)
			{
			case 24:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels); break;

			case 32:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels); break;

			default:
				DELTAENGINE_WARN("[Texture] Invalid bpp value: ", bpp); break;
			}

			glGenerateMipmap(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, 0);

			delete[] pixels;
		}

		Types::byte* Texture::loadImage(const char* filename, Types::uint32* width, Types::uint32* height, Types::uchar8* bpp)
		{
			FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(filename, 0);
			FIBITMAP *dib = nullptr;

			if (fif == FIF_UNKNOWN)
			{
				fif = FreeImage_GetFIFFromFilename(filename);
				if (fif == FIF_UNKNOWN) return nullptr;
			}

			if (FreeImage_FIFSupportsReading(fif)) dib = FreeImage_Load(fif, filename);

			if (!dib) return nullptr;

			Types::byte* pixels = FreeImage_GetBits(dib);

			*width = FreeImage_GetWidth(dib);
			*height = FreeImage_GetHeight(dib);
			*bpp = FreeImage_GetBPP(dib);

			/*RGBQUAD* quad = NEW RGBQUAD;
			quad->rgbBlue = 255;
			quad->rgbGreen = 0;
			quad->rgbRed = 255;
			quad->rgbReserved = 255;

			FreeImage_SetPixelColor(dib, *width - 1, *height - 1, quad);*/

			Types::uint32 size = *width * *height * *bpp / 8;

			Types::byte* result = NEW Types::byte[size];
			memcpy(result, pixels, size);

			FreeImage_Unload(dib);

			return result;
		}

		void* Texture::getPixels() const
		{
			Types::byte* out = NEW Types::byte[width * height * (bpp / 8)];

			glGetTextureImage(textureID, 0, bpp == 32 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, width * height * bpp / 8, out);

			return out;
		}

		void Texture::setData(const void* pixels) const
		{
			glBindTexture(GL_TEXTURE_2D, textureID);

			switch (bpp)
			{
			case 2:
				glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, pixels); break;

			case 24:
				glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels); break;

			case 32:
				glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels); break;

			default:
				DELTAENGINE_WARN("[Texture] Invalid bpp value: ", bpp); break;
			}

			/*if ((Memory::MemoryManager::getFlags(pixels) & Memory::AllocationFlags::MAGIC) == Memory::AllocationFlags::MAGIC)
			{
				delete[] pixels;
			}*/

			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}