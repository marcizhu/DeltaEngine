#pragma once

#include <vector>

#include "buffer.h"
#include "vector2d.h"
#include "renderer2d.h"
#include "texture.h"
#include "sprite.h"

namespace DeltaEngine {
	namespace Graphics {

		class Renderer2D;

		class Renderable2D
		{
		private:
			void setUVDefaults()
			{
				UV.push_back(Maths::Vector2D(0, 0));
				UV.push_back(Maths::Vector2D(0, 1));
				UV.push_back(Maths::Vector2D(1, 1));
				UV.push_back(Maths::Vector2D(1, 0));
			}

		protected:
			Maths::Vector2D position;
			Maths::Vector2D size;
			Types::uint32 color;
			std::vector<Maths::Vector2D> UV;
			Texture* texture;
			Sprite sprites;

			Renderable2D() : texture(nullptr) { setUVDefaults(); }

		public:
			Renderable2D(Maths::Vector2D& position, Maths::Vector2D& size, Types::Color& color) : position(position), size(size), texture(nullptr) { setUVDefaults(); setColor(color); }
			Renderable2D(Maths::Vector2D& position, Maths::Vector2D& size, Types::uint32 color) : position(position), size(size), color(color), texture(nullptr) { setUVDefaults(); }

			virtual ~Renderable2D() {}

			virtual void submit(Renderer2D* renderer) const { renderer->submit(this); }

			void setColor(unsigned int color) { this->color = color; }
			void setColor(const Types::Color& color) { this->color = color.getABGRColor(); }

			inline const Maths::Vector2D& getPosition() const { return position; }
			inline const Maths::Vector2D& getSize() const { return size; }
			inline const Types::uint32 getColor() const { return color; }
			inline const std::vector<Maths::Vector2D>& getUV() const { return UV; }
			inline const GLuint getTextureID() const { return sprites.getTextureCount() ? sprites.getCurrentTexture()->getID() : texture ? texture->getID() : 0; }
			inline Sprite& getSprite() { return sprites; }
			inline const Texture* getTexture() const { return sprites.getTextureCount() ? sprites.getCurrentTexture() : texture ? texture : nullptr; }

			inline void moveTo(float x, float y) { position.x = x; position.y = y; }
			inline void move(float dx, float dy) { position.x += dx; position.y += dy; }

		};
		
	}
}