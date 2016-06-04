#pragma once

#//include <FreeImage\FreeImage.h>

#include "texture.h"
#include "types.h"

using namespace DeltaEngine::Types;

namespace DeltaEngine {
	namespace Utils {

		class TextureUtils
		{
		private:

		public:
			static Graphics::Texture* drawRectangle(Graphics::Texture* tex, uint32 x1, uint32 y1, uint32 x2, uint32 y2, Color color);
			static Graphics::Texture* setPixel(Graphics::Texture* tex, uint32 x, uint32 y, Color color);
			static Graphics::Texture* drawCircle(Graphics::Texture* tex, uint32 x, uint32 y, uint32 radius, Color color);
			static Graphics::Texture* drawLine(Graphics::Texture* tex, uint32 x1, uint32 y1, uint32 x2, uint32 y2, Color color);

			static Graphics::Texture* setTransparentColor(Graphics::Texture* tex, Color color);
			static Graphics::Texture* replaceColor(Graphics::Texture* tex, Color original, Color newColor);

			static Graphics::Texture* rotate(Graphics::Texture* tex, float angle);

			static Graphics::Texture* flipHorizontal(Graphics::Texture* tex);
			static Graphics::Texture* flipVertical(Graphics::Texture* tex);
		};

	}
}